#include "so_stdio.h"

#define BUFFER_SIZE 4096
#define OP_MODE_SIZE 8
#define NON_RW_OP "default"
#define PREV_READ_OP "read"
#define PREV_WRITE_OP "write"

struct _so_file {
	int fd;
	unsigned char buffer[BUFFER_SIZE];
	int buf_len;
	int current_size;
	char mode[OP_MODE_SIZE];
	long cursor;
	long cursor_offset;
	int cursor_whence;
	int eof;
	int err;
	unsigned int file_permissions;
	unsigned int file_flags;
	pid_t child_process;
};

typedef struct _so_file SO_FILE;

int checkInvalidMode(const char mode);

int set_file_cursor(SO_FILE *stream);
