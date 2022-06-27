#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "so_stdio.h"
#include "utils.h"

/* Verific daca parametrul pentru modul de acces al unui fisier e valid */
int checkInvalidMode(const char mode)
{

	if (strchr("bcdefghijklmnopqstuvxyz", mode) != NULL)
		return 1;
	return 0;
}

/* Setez cursorul in fisier in functie de specificatiile din structura */
int set_file_cursor(SO_FILE *stream)
{

	int ret;

	ret = lseek(stream->fd, stream->cursor_offset, stream->cursor_whence);
	if (ret == -1)
	{
		stream->err++;
		return -1;
	}

	stream->cursor = ret;
	stream->cursor_offset = 0;
	stream->cursor_whence = 0;

	memset(stream->mode, 0, 8);
	strncpy(stream->mode, NON_RW_OP, 7);
	return 0;
}

/* Aloc structura destinata fisierului, dupa care il deschid in modul specificat */
SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	int potential_fd;
	SO_FILE *stream = (SO_FILE *)malloc(sizeof(*stream));

	if (stream == NULL)
		return NULL;

	memset(stream->buffer, 0, BUFFER_SIZE);
	stream->buf_len = 0;
	stream->current_size = 0;
	memset(stream->mode, 0, OP_MODE_SIZE);
	strncpy(stream->mode, NON_RW_OP, 7);
	stream->fd = 1;
	stream->cursor = 0;
	stream->cursor_offset = 0;
	stream->cursor_whence = 0;
	stream->eof = 0;
	stream->err = 0;
	stream->file_permissions = 0644;
	stream->file_flags = 0;
	stream->child_process = -1;

	/* Verific daca modul este valid */
	if (checkInvalidMode(mode[0]) == 1) {
		free(stream);
		stream = NULL;
		return NULL;
	}

	/* Pentru fiecare mod valid specific oflag-urile necesare */
	if (strcmp(mode, "r") == 0)
		stream->file_flags = stream->file_flags | O_RDONLY;

	if (strcmp(mode, "r+") == 0)
		stream->file_flags = stream->file_flags | O_RDWR;

	if (strcmp(mode, "w") == 0) {
		stream->file_flags = stream->file_flags | O_WRONLY;
		stream->file_flags = stream->file_flags | O_CREAT;
		stream->file_flags = stream->file_flags | O_TRUNC;
	}

	if (strcmp(mode, "w+") == 0) {
		stream->file_flags = stream->file_flags | O_RDWR;
		stream->file_flags = stream->file_flags | O_CREAT;
		stream->file_flags = stream->file_flags | O_TRUNC;
	}

	if (strcmp(mode, "a") == 0) {
		stream->file_flags = stream->file_flags | O_WRONLY;
		stream->file_flags = stream->file_flags | O_APPEND;
		stream->file_flags = stream->file_flags | O_CREAT;
	}

	if (strcmp(mode, "a+") == 0) {
		stream->file_flags = stream->file_flags | O_RDWR;
		stream->file_flags = stream->file_flags | O_APPEND;
		stream->file_flags = stream->file_flags | O_CREAT;
	}

	potential_fd = open(pathname, stream->file_flags, stream->file_permissions);
	if (potential_fd == -1) {
		free(stream);
		stream = NULL;
		return NULL;
	}

	stream->fd = potential_fd;

	return stream;
}

/* Functie care inchide fisierul si elibereaza structura SO_FILE */
int so_fclose(SO_FILE *stream)
{
	int ret = 0;

	/* Dau fflush la buffer si inchid fisierul */
	if (so_fflush(stream) == SO_EOF || close(stream->fd) == -1)
		ret = -1;

	stream->file_flags = 0;
	stream->file_permissions = 0;

	if (stream != NULL)
		free(stream);

	return ret;
}

/* Functie care citeste un caracter din fisier */
int so_fgetc(SO_FILE *stream)
{
	int ret;
	int chara;

	if (stream->current_size == stream->buf_len && so_fflush(stream) != SO_EOF) {

		ret = read(stream->fd, stream->buffer, BUFFER_SIZE);

		if (ret > 0) {
			stream->buf_len = ret;
			stream->current_size = 0;
		} else {
			stream->eof = 1;
			stream->err = stream->err + 1;
			return SO_EOF;
		}
	} else if (stream->current_size == stream->buf_len && so_fflush(stream) == SO_EOF) {

		stream->eof = 1;
		stream->err = stream->err + 1;
		return SO_EOF;
	}

	chara = (int)stream->buffer[stream->current_size];
	stream->current_size++;
	memset(stream->mode, 0, OP_MODE_SIZE);
	strncpy(stream->mode, PREV_READ_OP, 4);
	stream->cursor++;

	return chara;
}

/* Functie care scrie un caracter in fisier */
int so_fputc(int c, SO_FILE *stream)
{
	int ret;

	if (strncmp(stream->mode, PREV_READ_OP, 4) == 0
	|| strncmp(stream->mode, NON_RW_OP, 7) == 0) {
		memset(stream->buffer, 0, BUFFER_SIZE);
		stream->current_size = 0;
		stream->buf_len = BUFFER_SIZE;
	}

	memset(stream->mode, 0, OP_MODE_SIZE);
	strncpy(stream->mode, PREV_WRITE_OP, 5);
	stream->buffer[stream->current_size] = (unsigned char)c;
	stream->current_size++;
	stream->cursor++;

	if (stream->current_size == stream->buf_len && so_fflush(stream) == SO_EOF) {

		stream->eof = 1;
		stream->err++;
		return SO_EOF;
	} else if (stream->current_size == stream->buf_len && so_fflush(stream) != SO_EOF) {

		stream->buf_len = BUFFER_SIZE;
		stream->current_size = 0;
	}

	return c;
}

/* Citeste mai multe elemente, ce vor fi stocate la adresa lui ptr */
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int ret = 0;
	size_t no_elems, sz;

	if (strncmp(stream->mode, PREV_WRITE_OP, 5) == 0
	|| strncmp(stream->mode, NON_RW_OP, 7) == 0)
		ret = so_fflush(stream);

	memset(stream->mode, 0, OP_MODE_SIZE);
	strncpy(stream->mode, PREV_READ_OP, 5);
	for (no_elems = 0; no_elems < nmemb; no_elems++) {
		for (sz = 0; sz < size; sz++) {
			ret = so_fgetc(stream);
			if (ret < 0)
				return no_elems;
			memmove(ptr, &ret, sizeof(char));
			ptr++;
		}
	}

	return no_elems;
}

/* Scrie mai multe elemente din ptr in structura */
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int ret = 0;
	size_t no_elems, sz;
	int chara = 0;

	for (no_elems = 0; no_elems < nmemb; no_elems++) {
		for (sz = 0; sz < size; sz++) {
			memmove(&chara, ptr, sizeof(char));
			ret = so_fputc(chara, stream);
			if (ret == SO_EOF)
				return 0;
			ptr++;
		}
	}

	return no_elems;
}

/* Functie ce initiaza procesul de mutare a cursorului in fisier */
int so_fseek(SO_FILE *stream, long offset, int whence)
{
	int ret;

	if (strncmp(stream->mode, PREV_READ_OP, 4) == 0
	|| strncmp(stream->mode, NON_RW_OP, 7) == 0) {
		memset(stream->buffer, 0, BUFFER_SIZE);
		stream->buf_len = 0;
		stream->current_size = 0;
	} else {
		so_fflush(stream);
	}

	stream->cursor_offset = offset;
	stream->cursor_whence = whence;

	ret = set_file_cursor(stream);

	return ret;
}

/* Returnez cursorul din fisier */
long so_ftell(SO_FILE *stream)
{
	return stream->cursor;
}

/* Functie care goleste buffer-ul intern structurii si scrie content-ul lui in fisier */
int so_fflush(SO_FILE *stream)
{
	if (strncmp(stream->mode, PREV_WRITE_OP, 5) == 0) {

		int ret, buf_idx;

		for (buf_idx = 0; buf_idx < stream->current_size; buf_idx += ret) {

			size_t count = stream->current_size - buf_idx;
			const void *buf = stream->buffer + buf_idx;

			ret = write(stream->fd, buf, count);
			if (ret == -1)
				return SO_EOF;
		}

		stream->current_size = 0;
		stream->buf_len = 0;
		memset(stream->buffer, 0, BUFFER_SIZE);
	}

	return 0;
}

/* Returneaza file descriptor-ul fisierului curent */
int so_fileno(SO_FILE *stream)
{
	return stream->fd;
}

/* Verifica daca s-a ajuns la eof in fisier */
int so_feof(SO_FILE *stream)
{
	return stream->eof;
}

/* Verifica daca s-a produs vreo eroare */
int so_ferror(SO_FILE *stream)
{
	return stream->err;
}

/* Functie care deschide un proces nou si executa o comanda data ca parametru */
SO_FILE *so_popen(const char *command, const char *type)
{
	SO_FILE *stream = (SO_FILE *)malloc(sizeof(*stream));
	int pipefd[2];

	if (stream == NULL)
		return NULL;

	stream->buf_len = 0;
	stream->current_size = 0;
	memset(stream->buffer, 0, BUFFER_SIZE);
	memset(stream->mode, 0, OP_MODE_SIZE);
	strncpy(stream->mode, NON_RW_OP, 7);
	stream->fd = 1;
	stream->cursor = 0;
	stream->cursor_offset = 0;
	stream->cursor_whence = 0;
	stream->eof = 0;
	stream->err = 0;
	stream->file_permissions = 0644;
	stream->file_flags = 0;
	stream->child_process = -1;

	int ret = pipe(pipefd);
	int potential_fd;

	if (ret == -1) {
		free(stream);
		return NULL;
	}

	pid_t pid = fork();

	switch (pid) {
	case -1:
		close(pipefd[0]);
		close(pipefd[1]);
		free(stream);
		return NULL;

	case 0:
		if (strcmp(type, "w") == 0) {
			potential_fd = dup2(pipefd[0], 0);
			if (potential_fd == -1)
				return NULL;

			close(pipefd[1]);
		} else if (strcmp(type, "r") == 0) {
			potential_fd = dup2(pipefd[1], 1);
			if (potential_fd == -1)
				return NULL;

			close(pipefd[0]);
		} else {
			free(stream);
			return NULL;
		}

		if (execlp("/bin/sh", "/bin/sh", "-c", command, NULL) == -1) {
			free(stream);
			return NULL;
		}

		/* Inchid fie pipe[0] fie pipe[1] */
		close(potential_fd);

		free(stream);
		exit(0);
		break;

	default:
		if (strcmp(type, "w") == 0) {
			close(pipefd[0]);
			stream->fd = pipefd[1];
		} else if (strcmp(type, "r") == 0) {
			close(pipefd[1]);
			stream->fd = pipefd[0];
		} else {
			free(stream);
			return NULL;
		}
	}

	stream->child_process = pid;

	return stream;
}

/* Functie ce inchide un proces creat de so_popen */
int so_pclose(SO_FILE *stream)
{
	int ret = 0;
	int status;

	if (so_fflush(stream) == SO_EOF)
		ret = -1;

	close(stream->fd);

	if (waitpid(stream->child_process, &status, 0) == -1)
		ret = -1;

	free(stream);

	return ret;
}
