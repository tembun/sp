/*lnl-leading new line.*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 4096

int
main(void)
{
	char buf[BUFLEN];
	int inlen=1;
	char* in=(char*)malloc(1);
	in[0]='\n';
	ssize_t rdr;
	while((rdr=read(0,&buf,BUFLEN))>0)
	{
		buf[rdr]=0;
		inlen+=rdr;
		in=realloc(in,inlen);
		if(in==NULL)
		{
			dprintf(2,"err: error during allocating memory for input.\n");
			exit(1);
		}
		strcat(in,buf);
	};
	if(write(1,in,inlen)==-1)
	{
		dprintf(2,"err: cannot write to stdout.\n");
		exit(1);
	};
	return 0;
};