/*
 * esc -- escape input.
 *
 * Escaping means displaying newlines as `\n', tab characters as `\t' and so on.
 */

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SZ 4096

int
main()
{
	char bf[BUF_SZ]; /* Input buffer. */
	ssize_t rb; /* How many bytes we've read from stdin. */
	int i; /* Input buffer iterator. */
	char* r; /* Resulting escaped string. */
	int j; /* Current index of `r'. */
	int rl; /* Length of `r'. */
	char c; /* Character to be appended to `r'. */
	
	rb = 0;
	r = NULL;
	j = 0;
	rl = 0;
	
	/* Read stdin by portions. */
	while ((rb = read(STDIN_FILENO, &bf, BUF_SZ)) != 0) {
		if (rb < 0)
			err(1, "read()");
		
		/*
		 * Expand resulting string buffer by the length of current
		 * portion and reserve some arbitrary amount of extra space for
		 * escaped characters.
		 */
		if ((r = realloc(r, rl += (rb + rb / 2))) == NULL)
			err(1, "realloc()");
		
		/* Iterate over the input buffer. */
		for (i = 0; i < rb; i++) {
			/*
			 * We're going to insert two(or one, but two is maximum)
			 * characters and we need to make sure we've got enough
			 * space for them.
			 */
			if (j + 1 > rl) {
				/*
				 * Reserve 2 bytes for character we're going to
				 * insert right now plus allocate new space for
				 * the following part of input and also some
				 * extra space for escaped characters that may
				 * occur in that following part.
				 */
				if ((r = realloc(r, rl += (rb - i + 1) / 2)) ==
				    NULL)
					err(1, "realloc()");
			}
			
			/* By default, insert the character as is. */
			c = bf[i];
			switch (bf[i]) {
			case '\n':
				c = 'n';
				goto insert_slash;
			case '\t':
				c = 't';
				goto insert_slash;
			case '\\':
			case '\'':
			case '"':
			case '`':
			insert_slash:
				r[j++] = '\\';
				/* FALLTHROUGH. */
			default:
				r[j++] = c;
			}
		}
	}
	
	if (write(STDOUT_FILENO, r, j) < 0)
		err(1, "write()");
	free(r);
	
	return 0;
}
