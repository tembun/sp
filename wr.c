/*wr; wraps text lines.
it does it so that the maximum
line length will be 80 characters.
there are two main ways how line breaks:

1) if there already were spaces in the
current line, in case of length overflow
it'll substitute the last whitespace in
the line with newline character(\n) so
here is where the line breaks.

2) however, it may happen that there are no
whitespaces in the entire line of 80 characters.
as an example of it, consider, say, a source code for
C program - it may easily not have a space between
tokens up until the end of line(you just see at
the code below).
in this case, the program will break the line
by the means of inserting "\" character in
that long word and moving the rest part of it
on the next line. *in most cases*, this approach
works pretty nice with source code, but it's not
always that good for human-language texts
(you know, "-" character looks better for wrapping).
for this exact reason, one's able to specify
a character that will act as a wrap-character
as a first argument to the program.

You can use it with ~/bin/mdf script
in order to replace the target file in-place.*/

#include<unistd.h>
#include<stdlib.h>
int main(int argc,char** argv){
char ibu[4096];
char* obu;/*output buffer.*/
ssize_t rb;
int i;
int j;
int lsp;/*last space index in the line.*/
int chc;/*char count.*/
char sub;
if(argc==1)sub=92;
else sub=argv[1][0];
lsp=-1;
chc=0;
j=-1;
obu=0;
while((rb=read(0,&ibu,4096))>0){
	i=0;
	obu=realloc(obu,j+1+rb);
	if(!obu){
		write(2,"wr: can't realloc output buffer.\n",33);
		return 1;
	}
	while(i<rb){
		if(ibu[i]==32)lsp=j+1;
		if(ibu[i]==10){
			lsp=-1;
			chc=-1;
		}else if(chc>=80){
			if(lsp!=-1){
				if(lsp==j+1){
					++j;
					chc=0;
					obu[lsp]=10;
				}
				else{
					chc=j-lsp;
					obu[lsp]=10;
					++j;
					obu[j]=ibu[i];
				}
				lsp=-1;
				++i;
				continue;
			}else{
				obu=realloc(obu,j+3+rb);
				if(!obu){
					write(2,"wr: can't realloc output buffer.\n",33);
					return 1;
				}
				obu[j+2]=obu[j];
				obu[j+1]=10;
				obu[j]=sub;
				chc=2;
				j+=3;
				obu[j]=ibu[i];
				++i;
				continue;
			}
		}
		++chc;
		++j;
		obu[j]=ibu[i];
		++i;
	}
}
if(rb==-1){
	write(2,"wr: read error occured.\n",24);
	return 1;
}
write(1,obu,j+1);
free(obu);
return 0;
}
