#include<stdio.h>
#include<sys/stat.h>
int main()
{
    struct stat sfile;
    stat("hello.txt",&sfile);
    printf("st_mode is %o\n",sfile.st_mode);
    printf("st_uid is %d\n",sfile.st_uid);
    printf("st_size is %d\n",sfile.st_size);
}
