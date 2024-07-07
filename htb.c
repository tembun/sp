/*htb-html base.
usage:htb [name] [-c|-j]
-c add style tag
-j add script tag
build:cc -o htb htb.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc,char** argv)
{
	char hs[]="<!doctype html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\" >\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" >\n<link rel=\"shortcut icon\" href=\"#\">\n";
	char* c=NULL;
	char he[]="<title></title>\n</head>\n";
	char hens[]="<title>";
	char hene[]="</title>\n</head>\n";
	char bs[]="<body>\n";
	char* j=NULL;
	char be[]="</body>\n</html>";
	int cf,jf;
	int nlen,clen,jlen;
	char* n=NULL;
	if(argc>1)
	{
		int st=1;
		if(argv[1][0]!='-')
		{
			n=argv[1];
			nlen=strlen(n);
			st=2;
		}
		for(int i=st;i<argc;i++)
		{
			if(argv[i][0]=='-')
			{
				switch(argv[i][1])
				{
					case 'c':
					{
						cf=1;
						char cs[]="<link rel=\"stylesheet\" href=\"./";
						char* cn=(n?n:"index");
						char ce[]=".css\">\n";
						clen=strlen(cs)+(n?nlen:strlen(cn))+strlen(ce);
						c=malloc(clen*sizeof(*c));
						strcat(c,cs);
						strcat(c,cn);
						strcat(c,ce);
						break;
					};
					case 'j':
					{
						jf=1;
						char js[]="<script src=\"./";
						char* jn=(n?n:"index");
						char je[]=".js\"></script>\n";
						jlen=strlen(js)+(n?nlen:strlen(jn))+strlen(je);
						j=malloc(jlen*sizeof(*j));
						strcat(j,js);
						strcat(j,jn);
						strcat(j,je);
						break;
					};
				};
			};
		};
	};
	int l=strlen(hs)+(cf?clen:0)+strlen(hens)+(n?nlen:0)+strlen(hene)+strlen(bs)+(jf?jlen:0)+strlen(be);
	char* r;
	r=malloc(l*sizeof(*r));
	if(r==NULL)
	{
		dprintf(2,"err: error during allocation memory for output.\n");
		free(r);
		exit(1);
	}
	strcat(r,hs);
	if(cf)
	{
		strcat(r,c);
		free(c);
	}
	strcat(r,hens);
	if(n)
	{
		strcat(r,n);
	}
	strcat(r,hene);
	strcat(r,bs);
	if(jf)
	{
		strcat(r,j);
		free(j);
	}
	strcat(r,be);
	if(write(1,r,l)==-1)
	{
		dprintf(2,"err: error during writing to stdout.\n");
		exit(1);
	};
	free(r);
	return 0;
};