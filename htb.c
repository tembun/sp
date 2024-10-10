/*htb-html base.*/
#include <unistd.h>
int main()
{
	char s[]=(
"<!doctype html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"\t<meta charset=\"UTF-8\" >\n"
"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" >\n"
"\t<link rel=\"shortcut icon\" href=\"#\">\n"
"\t<title></title>\n"
"</head>\n"
"<body>\n"
"</body>\n"
"</html>\n"
);
write(1,&s,223);
return 0;
}