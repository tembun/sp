//cps-copy directory content in sorted order. only 1 depth lvl.
//src and dst paths should not contain trailing slash.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

char*
fp(char* s,char* e)
{char* r=malloc(strlen(s)+strlen(e)+2);if(r==NULL){write(2,"cannot malloc.\n",14);exit(1);};
strcpy(r,s);strcat(r,"/");strcat(r,e);
return r;};

void
srt(char** arr,int sz)
{
	for(int i=0;i<sz;i++)
	{
		for(int j=0;j<sz-1;j++)
		{
			for(int z=0;;z++)
			{
				if(arr[j][z]=='\0'){break;};
				if(arr[j][z]==arr[j+1][z]){continue;};
				if((arr[j+1][z]=='\0')||(arr[j][z]>arr[j+1][z]))
				{
					char* tmp=NULL;
					tmp=arr[j];
					arr[j]=arr[j+1];
					arr[j+1]=tmp;
				};
				break;
			};
		};
	};
};

int
main(int argc,char** argv)
{if(argc!=3){write(2,"src and dst dir paths are required.\n",36);exit(1);};
DIR* d=opendir(argv[1]);if(d==NULL){dprintf(2,"err: cannot open dir %s: %s.\n",argv[1],strerror(errno));exit(1);};
struct dirent* de=NULL;
char** dns=NULL;int dnssz=8;
dns=malloc(dnssz*sizeof(char*));if(dns==NULL){write(2,"cannot malloc dir names arr.\n",29);exit(1);};
int i=0;
while((errno=0),((de=readdir(d))!=NULL))
{
	if(i==dnssz){dns=realloc(dns,(dnssz*=2)*sizeof(char*));if(dns==NULL){write(2,"cannot realloc dir names arr.\n",30);exit(1);};};
	if(de->d_name[0]=='.'&&((de->d_name[1]=='\0')||((de->d_name[1]=='.')&&(de->d_name[2]=='\0')))){continue;};
	dns[i]=malloc(strlen(de->d_name)+1);if(dns[i]==NULL){write(2,"cannot malloc dir kid name.\n",28);exit(1);};
	strcpy(dns[i++],de->d_name);
};
if(errno!=0){dprintf(2,"err: cannot read dir %s: %s.\n",argv[1],strerror(errno));exit(1);};
if(closedir(d)==-1){dprintf(2,"err: cannot close dir %s: %s.\n",argv[1],strerror(errno));exit(1);};
if(i<dnssz){dns=realloc(dns,i*sizeof(char*));if(dns==NULL){write(2,"cannot realloc dir names arr.\n",30);exit(1);};};
srt(dns,i);
for(int j=0;j<i;j++)
{char* sfp=fp(argv[1],dns[j]);
char* dfp=fp(argv[2],dns[j]);
int sfd=open(sfp,O_RDONLY);if(sfd==-1){dprintf(2,"cannot open file %s: %s.\n",sfp,strerror(errno));exit(1);};
int dfd=open(dfp,O_WRONLY|O_CREAT,0644);if(dfd==-1){dprintf(2,"cannot open file %s: %s.\n",dfp,strerror(errno));exit(1);};
char bf[4096];ssize_t rb;
while(rb=read(sfd,&bf,4096)){if(!write(dfd,&bf,rb)){dprintf(2,"cannot write to %s: %s.\n",dfp,strerror(errno));exit(1);};};
if(close(sfd)==-1){dprintf(2,"cannot close file %s: %s.\n",sfp);exit(1);};
if(close(dfd)==-1){dprintf(2,"cannot close file %s: %s.\n",dfp);exit(1);};
free(sfp);free(dfp);
free(dns[j]);
};
free(dns);
return 0;};