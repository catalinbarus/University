#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "exec_parser.h"

static so_exec_t *exec;

/* Handler folosit pentru semnalul SIGSEGV */
static struct sigaction previous_handler;

/* File descriptor static folosit pentru deschiderea executabilului */
static int fd;

/* Structura ajutatoare folosita in campul data din structura o_seg_t */
typedef struct segment_data {
	int page_size;
	int mapped;
} segment_data_t;

/* Functie ce cauta eventualul segment in care se afla adresa */
int find_segment(siginfo_t *info)
{
	for (int i = 0; i < exec->segments_no; i++) {

		void *vaddr = (void *) exec->segments[i].vaddr;
		unsigned int mem_size = exec->segments[i].mem_size;

		if (info->si_addr >= vaddr && info->si_addr < vaddr + mem_size)
			return i;
	}

	return -1;
}

/* Functie ce implementeaza logica maparii unei pagini */
void page_map(so_seg_t segment, segment_data_t *segment_data, int page_map_addr)
{
	int anonymous_map_flags = MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS;
	int write_map_flags = MAP_PRIVATE | MAP_FIXED;
	int page_size = segment_data->page_size;

	int ret;
	void *ptr;

	void *addr = (void *) segment.vaddr + page_map_addr * page_size;

	/* Daca trebuie sa scriem date din fisier */
	if (segment.file_size > page_map_addr * page_size) {
		/* Mutam cursorul unde este indicat de offset */
		ret = lseek(fd, segment.offset + page_map_addr * page_size, SEEK_SET);

		if (ret == -1)
			exit(EXIT_FAILURE);

		ptr = mmap(addr, page_size, PERM_W, write_map_flags, fd, ret);

		if (ptr == MAP_FAILED)
			exit(EXIT_FAILURE);

		if (segment.file_size < (page_map_addr + 1) * page_size) {
			void *str = (void *)segment.vaddr + segment.file_size;

			memset(str, 0, (page_map_addr + 1) * page_size - segment.file_size);
		}

	} else {

		ptr = mmap(addr, page_size, PERM_W, anonymous_map_flags, -1, 0);

		if (ptr == MAP_FAILED)
			exit(EXIT_FAILURE);
	}

	/* Setam protectia paginii curente */
	ret = mprotect(ptr, page_size, segment.perm);

	if (ret == -1)
		exit(EXIT_FAILURE);
}

/* Functie ce implementeaza handler-ul semnalului SIGSEGV */
static void pfhandler(int signum, siginfo_t *info, void *context)
{
	/* Daca nu dam de SIGSEGV, folosim handler-ul precedent */
	if (signum != SIGSEGV) {
		previous_handler.sa_sigaction(signum, info, context);
		return;
	}

	int ret;

	/* Cautam adresa ce apartine segmentului */
	ret = find_segment(info);

	/* Daca o gasim verificam maparile */
	if (ret != -1) {

		int page_map_addr, page_size;
		so_seg_t segment;
		segment_data_t *segment_data = NULL;

		segment = exec->segments[ret];
		segment_data = (struct segment_data *) segment.data;

		page_size = segment_data->page_size;
		page_map_addr = ((uintptr_t) info->si_addr - segment.vaddr) / page_size;

		/* Daca am mapat deja aceasta pagina, doar rulam handler-ul precedent */
		if (segment_data->mapped == page_map_addr) {
			previous_handler.sa_sigaction(signum, info, context);
			return;
		}

		/* Apelam functia ce va mapa pagina */
		page_map(segment, segment_data, page_map_addr);

		/* Retin in structura datele despre noua pagina */
		segment_data->mapped = page_map_addr;
	}

	/* Daca nu o gasim, doar rulam handler-ul precedent */
	else {
		previous_handler.sa_sigaction(signum, info, context);
		return;
	}
}

/* Functie ce initializeaza un nou handler */
int so_init_loader(void)
{
	int ret;
	struct sigaction new_handler;

	new_handler.sa_flags = SA_SIGINFO;
	new_handler.sa_sigaction = pfhandler;

	ret = sigemptyset(&new_handler.sa_mask);
	if (ret < 0)
		return -1;

	ret = sigaddset(&new_handler.sa_mask, SIGSEGV);
	if (ret < 0)
		return -1;

	ret = sigaction(SIGSEGV, &new_handler, &previous_handler);
	if (ret < 0)
		return -1;

	return 0;
}

/* Functie ce incepe executia programului */
int so_execute(char *path, char *argv[])
{
	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	int i, page_size = getpagesize();

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);

	/* Initializam structura segment_data in campul de data din so_seg_t */
	for (i = 0; i < exec->segments_no; i++) {
		exec->segments[i].data = (segment_data_t *) malloc(sizeof(segment_data_t));

		if (exec->segments[i].data == NULL)
			exit(EXIT_FAILURE);

		segment_data_t *data = exec->segments[i].data;

		memset(data, 0, sizeof(segment_data_t));

		data->page_size = page_size;
		data->mapped = -1;
	}

	so_start_exec(exec, argv);

	return -1;
}
