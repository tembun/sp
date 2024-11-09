/*
fl -- create a first hard link to a file(s).

I consider it as an utility
for creating files(actually, creating
a first hard link to them), instead
of touch(1), which seems to be for
setting file timestamps.
*/

#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char** argv){
int i;
struct stat st;

if(argc < 2){
	write(2,"fl: specify at least one name for a file to create a link for.\n",63);
	return 1;
}

i=1;
while(i<argc){
	if(!stat(argv[i],&st)){
		dprintf(2,"fl: %s exists already.\n", argv[i]);
		goto next;
	}

	/*
	DEFFILEMODE is for default file mode, which
	is 666 (but bear in mind, it'll be restricted
	by umask(2)).
	For DEFFILEMODE, see /usr/include/sys/stat.h.
	For file permission defines, see stat(2).
	*/
	if(open(argv[i],O_CREAT|O_WRONLY,DEFFILEMODE) == -1) {
		dprintf(2,"fl: can't create %s.\n",argv[i]);
	}

	next:
	++i;
}

return 0;
}
