#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


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
	int idx = 0;
	char buf[1024];
	char reverse_buf[1024];
	char tmp[1024];

	open_sursa = open(argv[1], O_RDONLY);

	if (open_sursa < 0) {
		fatal("Error: Cannot open file.\n");
	}

	lseek(open_sursa, 0, SEEK_SET);

	while ((copiat = read(open_sursa, buf, sizeof(buf)))) {
		if (copiat < 0) {
			fatal("Error occured at reading file.");
		}

		for (int i = copiat - 1; i >= 0 ; i--) {

			if (buf[i] != '\n') {
				tmp[idx] = buf[i];
				idx++;
			}

			else if(buf[i] == '\n' && i != (copiat - 1)) {

				int cnt = 0;
				int idx_copy = idx - 1;
				while (cnt < idx) {
					reverse_buf[cnt] = tmp[idx_copy];
					idx_copy--;
					cnt++;
				}

				reverse_buf[cnt] = '\n';
				write(1, reverse_buf, cnt+1);
				idx = 0;
				tmp[0] = '\0';
			}

			if (i == 0) {

				int j = 0;
				while(buf[j] != '\n') {

					write(1, buf + j, 1);
					j++;

				}

				write(1, "\n", 1);
			}
		}

		if (copiat < 0) {
			fatal("Error occured at writing file.");
		}
	}

	close(open_sursa);

	return 0;



}