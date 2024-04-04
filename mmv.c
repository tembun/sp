/*mmv-multiple mv.
allows to perform multiple mv calls at once.
usage: mmv src1 dst1 src2 dst2...*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

extern char** environ;

int
main(int argc, char** argv)
{	if(argc==1)
	{
		dprintf(2,"err: missing file operands.\n");
		exit (1);
	}	
	if((argc & 0b1) == 0)
	{
		dprintf(2, "err: missing destination file operand for '%s'.\n",argv[argc-1]);
		exit(1);
	}
	for(int i=1;i<argc-1;i+=2)
	{
		pid_t forkr=fork();
		if(forkr==-1)
		{
			dprintf(2,"err: error while forking process.\n");
			exit(1);
		}
		if(forkr==0)
		{
			char* src=argv[i];
			char* dst=argv[i+1];
			char* mvargv[]={"mv",src,dst,NULL};
			if(execve("/usr/bin/mv",mvargv,environ)==-1)
			{
				dprintf(2,"err: error during /usr/bin/mv execution. error code: %d.\n",errno);
				exit(1);
			};
		}
	};
	return 0;
};