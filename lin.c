/*lin-obtain specified line or line range from stdin.
range is specified in form: <start>,[<end>].
if the delimiter is present, but the end boundary
is not, the rest lines from the <start>
line inclusively will be spited out.*/
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char** argv){
char buf[4096];
ssize_t rb;
int lr;
int i;
int j;
int resl;
int rng;/*an index of a range delimiter (',').*/
char toend;/*in case args are: <arg1>,<none>.*/
char staf;/*was the start of the range found.*/
int sta;
int fin;
char* stas;
char* fins;
char* res;
stas=0;
fins=0;
staf=0;
res=0;
lr=0;
resl=0;
j=0;
if(argc==1){
	write(2,"lin: specify a line number to obtain.\n",38);
	return 1;
}
stas=malloc(16);
if(!stas){
	write(2,"can't allocate input buffer.\n",29);
	return 1;
}
i=0;
rng=0;
while(1){
	if(argv[1][i]==44){
		rng=i;
		stas[i]=0;
		fins=malloc(16);
		if(!fins){
			write(2,"can't alloc input buffer.\n",29);
			return 1;
		}
		++i;
		continue;
	}
	if(rng)fins[i-rng-1]=argv[1][i];
	else stas[i]=argv[1][i];
	if(!argv[1][i])break;
	++i;
}
sta=atoi(stas);
if(rng){
	toend=!fins[0];
	if(toend)goto valid;
	fin=atoi(fins);
}
valid:
if(sta<=0||(!toend&&fin<=0)){
	write(2,"lin: line number should be greater than 0.\n",43);
	return 1;
}
if(!toend&&fin<sta){
	write(2,"lin: wrong range specified.\n",28);
	return 1;
}
while((rb=read(0,&buf,4096))>0){
	resl+=rb;
	res=realloc(res,resl);
	if(!res){
		write(2,"lin: can't realloc result buffer.\n",34);
		return 1;
	}
	i=0;
	while(i<rb){
		res[j++]=buf[i];
		if(buf[i++]==10){
			++lr;
			if(staf){
				if(lr==fin)goto succ;
			}else{
				if(lr==sta){
					if(rng)staf=1;
					else goto succ;
				}else j=0;
			}
		}
	}
}
if(!rng){
	write(2,"lin: no such line.\n",19);
	return 1;
}else if(!toend){
	write(2,"lin: wrong range boundary.\n",27);
	return 1;
}
succ:
write(1,res,j);
free(res);
return 0;
}
