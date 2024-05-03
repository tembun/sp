//eye-damn simple eye file content.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/inotify.h>
#include <errno.h>
#define BSZ 4096
#define E()write(1,"\x1b[2J\x1b[0;0H",10);lseek(fd,0,SEEK_SET);while((r=read(fd,&bf,BSZ))>0){write(1,&bf,r);};
char bf[BSZ];
int fd;
int r;

int
main(int argc,char** argv)
{if(argc!=2){write(2,"wrong arg count.\n",17);exit(1);};
int nfd=inotify_init();if(nfd==-1){dprintf(2,"cannot init inotify: %s.\n",strerror(errno));};
int wd=inotify_add_watch(nfd,argv[1],IN_MODIFY);if(wd==-1){dprintf(2,"cannot eye file %s: %s.\n",argv[1],strerror(errno));exit(1);};
struct inotify_event ne={0};
if((fd=open(argv[1],O_RDONLY))==-1){dprintf(2,"cannot open file %s: %s.\n",argv[1],strerror(errno));};
E();while(1){if(read(nfd,&ne,sizeof(ne))!=-1){E();}else{dprintf(2,"cannot read from inotify.\n");exit(1);};};
return 0;};