#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


void fatal(char * mesaj_eroare)
{
    perror(mesaj_eroare);
    exit(0);
}


int main(int argc, char *argv[]) {

	if (argc != 2) {
		return -1;
	}

	int open_sursa;
	int copiat;
	char buf[1024];

	open_sursa = open(argv[1], O_RDONLY);

	if (open_sursa < 0) {
		fatal("Error: Cannot open file.\n");
	}

	lseek(open_sursa, 0, SEEK_SET);

	while ((copiat = read(open_sursa, buf, sizeof(buf)))) {
		if (copiat < 0) {
			fatal("Error occured at reading file.");
		}

		copiat = write(1, buf, copiat);
		if (copiat < 0) {
			fatal("Error occured at writing file.");
		}
	}

	close(open_sursa);

	return 0;



}