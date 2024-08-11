#include<stdio.h>
int main(int argc,char** argv){
char c;
char s[32][4]={"NUL","SOH","STX","ETX","EOT","ENQ",
"ACK","BEL","BS ","TAB","LF ","VT ","FF ","CR ","SO ","SI ",
"SLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
"CAN","EM ","SUB","ESC","FS ","GS ","RS ","US "};
if(argc>1){
int i;
i=1;
while(i<argc){
if(argv[i][0]==92&&argv[i][1]==110){dprintf(1,"\\n:%d\n",'\n');++i;}
else if(argv[i][0]==92&&argv[i][1]==116){dprintf(1,"\\t:%d\n",'\t');++i;}
else dprintf(1,"%c:%d\n",argv[i][0],argv[i++][0]);
};
return 0;
}
c=0;
while(1){
if(c<100)dprintf(1," ");
if(c<10)dprintf(1," ");
if(c==127){dprintf(1,"127: DEL\n");break;}
if(c<32)dprintf(1,"%d: %s  ",c,s[c]);
else dprintf(1,"%d: %c  ",c,c);
if(c>111){dprintf(1,"\n");c=(c%16)+1;}
else c+=16;}
return 0;}