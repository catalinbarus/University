/**
 * SO
 * Lab #2, Simple I/O operations
 *
 * Task #3, Linux
 *
 * cat/cp applications
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"
#include "xfile.h"

#define BUFSIZE 32

int main(int argc, char **argv)
{
	int fd_src;
	int fd_dst;
	int rc;
	int bytesRead;
	char buffer[BUFSIZE];

	if (argc < 2 || argc > 3) {
		printf("Usage:\n\t%s source_file [destination_file]\n",
			   argv[0]);
		return 0;
	}

	/* TODO 1 - Open source file for reading */
	fd_src = open(argv[1], O_RDONLY);
	DIE(fd_src < 0, "fail at opening file");

	if (argc == 3) {
		/* TODO 2 - Redirect stdout to destination file */
		
		fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0644);
		DIE(fd_dst < 0, "failed to open destination");

		rc = dup2(fd_dst, STDOUT_FILENO);
		DIE(rc < 0, "fail at dup2");

		rc = close(fd_dst);
		DIE(rc < 0, "failed to close fd2");
	}

	/**
	 * TODO 1 - Read from file and print to stdout
	 * use _only_ read and write functions
	 * for writing to output use write(STDOUT_FILENO, buffer, bytesRead);
	 */
	while ((bytesRead = read(fd_src, buffer, BUFSIZE)) != 0) {
		DIE(bytesRead < 0, "read failed");

		buffer[bytesRead] = '\0';

		rc = write(STDOUT_FILENO, buffer, bytesRead);
		/* write(STDOUT_FILENO, buffer, bytesRead); */

		DIE(rc < 0, "write failed");
	}

	/**
	 * TODO 3 - Change the I/O strategy and implement xread/xwrite. These
	 * functions attempt to read _exactly_ the size provided as parameter.
	 */

	/* TODO 1 - Close file */
	rc = close(fd_src);
	DIE(rc < 0, "close fd");

	return 0;
}
