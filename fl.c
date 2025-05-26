/*
 * fl -- create a first hard link to a file(s).
 */

#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char** argv)
{
	int i;
	struct stat st;
	
	if (argc < 2) {
		errx(1, "Usage: fl file ...");
		return 1;
	}
	
	i = 1;
	while(i < argc) {
		if (stat(argv[i],&st) == 0) {
			dprintf(STDERR_FILENO,
			    "[fl]: %s already exists\n", argv[i]);
			goto next;
		}
	
		/*
		 * DEFFILEMODE is for default file mode, which is 666 (but bear
		 * in mind, it'll be restricted by umask(2)).
		 *
		 * For DEFFILEMODE, see /usr/include/sys/stat.h.
		 * For file permission defines, see stat(2).
		 */
		if (open(argv[i], O_CREAT | O_WRONLY, DEFFILEMODE) == -1)
			dprintf(STDERR_FILENO, "[fl]: Can't create %s: %s\n",
			    argv[i], strerror(errno));
next:
		i++;
	}
	
	return 0;
}
