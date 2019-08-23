#include <stdio.h>

int main () {
   FILE *fp;

   fp = fopen("file.txt", "a+");
   char temp[50];
   fputs("This is c programming.", fp);
   fputs("This is a system programming language.", fp);
   fclose(fp);
   fp = fopen("file.txt", "r");
   while(fgets(temp, sizeof(temp), fp) != NULL)
	{
		printf("here\n");
		printf("%s\n",temp);
    }
   
   return(0);
}