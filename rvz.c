/*rvz-home revizion.
displays contents of hidden directories in home recursively.
build: cc -o rvz rvz.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define NLIM 18
#define LLIM 18

void
ls(char* dp,char lvl)
{
	char rt=lvl==0;
	DIR* d=opendir(dp);
	if(d==NULL)
	{
		dprintf(2,"err: cannot open dir %s: %s.\n",dp,strerror(errno));
		exit(1);
	}
	struct dirent* de=NULL;
	char idx=0;
	while((errno=0),(de=readdir(d)))
	{
		unsigned nlen=strlen(de->d_name);
		char fdot=de->d_name[0]=='.';
		if(fdot&&((nlen==1)||(de->d_name[1]=='.'&&nlen==2)))
		{continue;};
		if(rt)
		{
			if(!fdot){continue;};
		}
		else
		{
			char* lvls=NULL;
			lvls=malloc(lvl+1);
			if(lvls==NULL)
			{
				dprintf(2,"err: cannot allocate memory for tabbed string.\n");
				exit(1);
			};
			for(int i=0;i<lvl;i++)
			{
				lvls[i]='\t';
			};
			lvls[lvl]='\0';
			dprintf(1,"%s",lvls);
			free(lvls);
			if(idx>LLIM)
			{
				dprintf(1,"...\n");
				break;
			}
		};
		if(nlen>NLIM)
		{
			char* dln=malloc(NLIM+4);
			if(dln==NULL)
			{
				dprintf(2,"err: cannot allocate memory for long file name.\n");
				exit(1);
			};
			strncpy(dln,de->d_name,NLIM);
			dln[NLIM]='\0';
			strcat(dln,"...");
			dprintf(1,"%s",dln);
			free(dln);
		}
		else
		{
			dprintf(1,"%s",de->d_name);
		}
		if(de->d_type==DT_DIR)
		{
			dprintf(1,"/");
		}
		dprintf(1,"\n");
		if(de->d_type==DT_DIR)
		{
			char* kidp=NULL;
			char dplen=strlen(dp);
			kidp=malloc(dplen+nlen+2);
			if(kidp==NULL)
			{
				dprintf(2,"err: cannot allocate memory for dir path.\n");
				exit(1);
			};
			strcpy(kidp,dp);
			kidp[dplen]='/';
			kidp[dplen+1]='\0';
			strcat(kidp,de->d_name);
			ls(kidp,lvl+1);
			free(kidp);
		};
		idx++;
	};
	if(errno)
	{
		dprintf(2,"err: error during reading dir %s: %s",dp,strerror(errno));
		exit(1);
	};
	if(closedir(d)==-1)
	{
		dprintf(2,"err: cannot close dir %s: %s",dp,strerror(errno));
		exit(1);
	};
};

int
main(void)
{
	char* hm=getenv("HOME");
	if(hm==NULL)
	{
		dprintf(2,"err: HOME env var is not specified.\n");
		exit(1);
	};
	ls(hm,0);
	return 0;
};