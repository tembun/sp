#include<unistd.h>
#include<stdlib.h>
int main(int argc,char** argv){
char buf[4096];
ssize_t rb;
int lr;
int lin;
int i;
int j;
int resl;
char* res;
res=0;
lr=0;
resl=0;
j=0;
if(argc==1){
	write(2,"lin: specify a line number to obtain.\n",38);
	return 1;
}
lin=atoi(argv[1]);
if(lin<=0){
	write(2,"lin: line number should greater than 0.\n",40);
	return 1;
}
while((rb=read(0,&buf,4096))>0){
	resl+=rb;
	res=realloc(res,resl);
	if(res==0){
		write(2,"lin: can't realloc result buffer.\n",34);
		return 1;
	}
	i=0;
	while(i<rb){
		res[j++]=buf[i];
		if(buf[i++]==10){
			++lr;
			if(lr==lin)goto prnt;
			j=0;
		}
	}
}
if(lin!=1){
	write(2,"lin: no such line.\n",19);
	return 1;
}
prnt:
write(1,res,j);
free(res);
return 0;
}
