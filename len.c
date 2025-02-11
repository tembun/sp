/*len -- string length. reads string from stdin and sends its length in bytes to stdout*/
#include<unistd.h>
#include<stdlib.h>
int main(){
char buf[4096];/*stdin buffer.*/
ssize_t rb;/*read bytes.*/
int l;/*input string length (number).*/
int ldc;/*length digit count.*/
int j;/*iterator for filling result string (initially copy of ldc variable).*/
int z;/*temporary variable for getting length digit count (copy of l variable).*/
int i;/*input buffer iterator.*/
char* rs;/*resulting string.*/
l=0;
ldc=0;
while((rb=read(0,&buf,4096))>0) {
	i=0;
	while (i<rb) {
		if (buf[i] != '\n' && buf[i] != '\r') l+=1;
		++i;
	}
}
if(rb==-1){write(2,"can't read stdin\n",17);return 1;}
/*getting l variable number value decimal digit count*/
z=l;
while(z){
ldc++;
z/=10;
}
/*reserve memory for resulting string*/
rs=malloc(ldc+1);
if(!rs){write(2,"can't alloc\n",12);return 1;}
/*fill resulting string from end to the begining*/
j=ldc;
rs[j]=10;
while((j--)>-1){
rs[j]=(l%10)+48;
l/=10;
}
write(1,rs,ldc+1);/*write resulting string to stdout.*/
return 0;}
