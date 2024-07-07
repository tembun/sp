/*esc-escape(\n->\\n and so on) string from stdin and write it to stdout.*/
#include<unistd.h>
#include<stdlib.h>
int
main(){
char bf[4096];//input buffer
ssize_t rb=0;//how many bytes were read from stdin
int i;//input buffer iteration index
char* r=0;//resulting escaped string
int j=0;//current index of resulting string
int rl=0;//length of resulting string buffer. need it for realloc
char c;//charcter to be appended to result
/*read stdin by portions*/
while((rb=read(0,&bf,4096))>0){
/*expand resulting string buffer by the length of current
portion AND reserve some arbitrary amount of extra space for escaped
characters. actually, it's a 1.5*rb.*/
r=realloc(r,rl+=(rb+(rb>>1)));
if(!r){write(2,"can't realloc.\n",15);return 1;}
i=0;//every time start buffer iteration from its begining
/*iterate over the input buffer*/
while(i<rb){
/*we're going to insert two(or one, but two is maximum) characters and we need to
ensure we've got enough space for them*/
if((j+1)>rl){//if there is no enough space
/*reserve 2 bytes for character we're going to insert right now
plus allocate new space for the following part of input and also some
extra space for escaped chars that may occur in that following part ofinput too*/
r=realloc(r,rl+=(2+((rb-i-1)>>1)));
if(!r){write(2,"can't realloc.\n",15);return 1;}
}
c=bf[i];//by default we're goint to insert character as it is.
switch(bf[i]){
/*in case of control characters, we need to manually specify characters that are next
to the \ character*/
case '\n':c='n';goto is;
case '\t':c='t';goto is;
/*in case of quotes and slash symbol we also need to prepend them with \ and write
them as they are.*/
case '\\':
case '\'':
case '"':
case '`':/*insert slash label*/is:{
r[j++]='\\';//insert slash character
}
default:{
r[j++]=c;//insert character we've specified before
++i;//continue input buffer iteration
}
}
}
}
/*here we might leave the read loop not because we've reached the end,
but because of the error occured*/
if(rb==-1){write(2,"can't read stdin.\n",18);return 1;}
write(1,r,j);//write resulting string to stdout
free(r);//free resulting string memory
return 0;}