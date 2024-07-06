/*ues-unescape(\\n->\n and so on) string from stdin and send it to stdout.*/
#include<unistd.h>
#include<stdlib.h>
int
main(){
char buf[4096];//input buffer
ssize_t rb;//input read byte count
int i;//iterator for input buffer
char* r;//resulting string with unescaped string
int j=0;//index of next result string character
int d=1;//delta, used in uc label. 0-check current symbol, 1-check next symbol.
char cc=0;//control character will be used for replacement
char cf=0;//carry flag. indicates if previous char was \
/*read stdin into buffer*/
while((rb=read(0,&buf,4096))>0){
r=realloc(r,j+4096);
if(!r){write(2,"can't realloc r.\n",17);return 1;}
i=0;//start iteration from the buffer begining
while(i<rb){//loop over the buffer we've just read a portion of input in
if(cf){//check carry flag
cf=0;
/*in uc we're going to check current symbol, not the next one, so set d to 0
and jump into uc*/
d=0;goto uc;//this behaviour is described a few lines below
}
if(buf[i]=='\\'){
if(i<rb-1){//if next character exist
	d=1;//if we reach uc label from the condition above, we want to check next symbol
	/*unescaped char*/uc:switch(buf[i+d]){
	case 'n':cc='\n';break;
	case 't':cc='\t';break;
	case '\\':
	case '/':
	case '"':
	case '`':
	case '\'':cc=buf[i+d];break;
	/*otherwise char combination with slash doesn't make sense, so print them as they are*/
	default:{
		cc=buf[i+d];r[j++]='\\';//insert \ then character itself.
		break;
	}
	}
	r[j++]=cc;//insert control character(or \+char if it's not an escape sequence)
	i+=(d+1);continue;
}else{
	/*here: current buffer has been ended with \ char. now there are two possibilities:
	1: it was the end of the entire input, in this case we treat that trailing \ as \
	itself and append it to the resulting string.
	2: it wasn't the end of input, so we need to handle first char of next buffer
	read cycle in a unique way, actually we need to perform exactly the same operations that
	are under "uc" label.
	*/
	cf=1;break;//set the carry flag and wait if input will continue
}
}
/*if char is not a \, then simply append it to the resulting string*/
r[j++]=buf[i++];
}
}
if(rb==-1){write(2,"can't read.\n",12);return 1;}
/*here: we need to check carry flag again if \ occurs in the very end of input*/
if(cf){
r[j++]='\\';//append bare slash to the end of result
}
write(1,r,j);//write result to stdout
free(r);//free resulting string
return 0;}