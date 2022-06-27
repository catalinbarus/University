/**
 * SO
 * Lab #12
 *
 * Task 01 - mini.c
 * Implementing a minimal comand line file utility
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <sys/mount.h>

#include "utils.h"

#define MAX_LINE_SIZE		256

const char *delim = " \t\n";
char *prompt = "so-lab12";

#define TODO2
#define TODO3
#define TODO4
#define TODO5
//#define TODO6
//#define TODO7

int main(void)
{
	char line[MAX_LINE_SIZE];
	char *cmd;
	char *arg1;
	char *arg2;
	char *arg3;
	int ret; /* to be used for function calls return code */

	while (1) {
		printf("<%s>", prompt);
		fflush(stdout);

		memset(line, 0, MAX_LINE_SIZE);

		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(EXIT_SUCCESS);

		cmd = strtok(line, delim);
		if (!cmd)
			continue;
#ifdef DEBUG
		printf("Executing command: %s\n", cmd);
#endif
		if (strncmp(cmd, "quit", 4) == 0)
			break;
#ifdef TODO2
		/**
		 * TODO2: implement list <device_node>
		 * Output: <c|b> <major>:<minor>
		 * e.g: list /dev/zero
		 * Output: /dev/zero: <c> 1:5
		 */
		if (strncmp(cmd, "list", 4) == 0) {
			struct stat s_buf;
			char type = 'N';

			arg1 = strtok(NULL, delim); /* device_node name */
			if (!arg1)
				continue;

			ret = stat(arg1, &s_buf);
			DIE(ret < 0, "stat failed");

			if (S_ISCHR(s_buf.st_mode))
				type = 'C';
			if (S_ISBLK(s_buf.st_mode))
				type = 'B';

			printf("%s: <%c> %d:%d\n", arg1, type,
				major(s_buf.st_rdev), minor(s_buf.st_rdev));
		}
#endif

#ifdef TODO3
		/**
		 * TODO3: implement mount source target fs_type
		 * e.g: mount /dev/sda1 /mnt/disk2 ext3
		 */
		if (strncmp(cmd, "mount", 5) == 0) {
			arg1 = strtok(NULL, delim); /* source */
			arg2 = strtok(NULL, delim); /* target */
			arg3 = strtok(NULL, delim);/* fs_type (e.g: ext2) */

			ret = mount(arg1, arg2, arg3, 0, NULL);
			DIE(ret < 0, "mount error");
		}
		if (strncmp(cmd, "umount", 6) == 0) {
			/* TODO3: implement umount */
			arg1 = strtok(NULL, delim); /* target */

			ret = umount(arg1);
			DIE(ret < 0, "umount error");
		}
#endif

#ifdef TODO4
		/**
		 * TODO4: implement symlink oldpath newpath
		 * e.g: symlink a.txt b.txt
		 */
		if (strncmp(cmd, "symlink", 7) == 0) {
			arg1 = strtok(NULL, delim); /* oldpath */
			arg2 = strtok(NULL, delim); /* newpath */

			ret = symlink(arg1, arg2);
			DIE(ret < 0, "symlinking error");
		}
		if (strncmp(cmd, "unlink", 6) == 0) {
			/* TODO4: implement unlink */
			arg1 = strtok(NULL, delim); /* pathname */

			ret = unlink(arg1);
			DIE(ret < 0, "unlinking error");
		}
#endif

#ifdef TODO5
		/**
		 * TODO5: implement mkdir pathname mode
		 * e.g: mkdir food 0777
		 */
		if (strncmp(cmd, "mkdir", 5) == 0) {
			arg1 = strtok(NULL, delim); /* pathname */

			ret = mkdir(arg1, (mode_t)0755);
			DIE(ret < 0, "mkdir error");
		}
		if (strncmp(cmd, "rmdir", 5) == 0) {
			/* TODO5: implement rmdir pathname */
			arg1 = strtok(NULL, delim); /* pathname */

			ret = rmdir(arg1);
			DIE(ret < 0, "rmdir error");
		}
#endif

#ifdef TODO6
		/**
		 * TODO6: implement ls dirname
		 * e.g: ls ..
		 */
		if (strncmp(cmd, "ls", 2) == 0) {
			/* recursively print files starting with arg1 */
			arg1 = strtok(NULL, delim);

		}
#endif

#ifdef TODO7
		if (strncmp(cmd, "chdir", 5) == 0) {
			/**
			 * TODO7: implement chdir <dir>
			 * e.g: chdir bar
			 */
			arg1 = strtok(NULL, delim); /* pathname */
		}

		if (strncmp(cmd, "pwd", 3) == 0) {
			/**
			 * TODO7: implement pwdir
			 * e.g: pwd
			 */
			/* print workding directory */
		}
#endif
	}

	return 0;
}
