#include<stdio.h>
#include<errno.h>
#include<string.h>

int main()
{
    ///这一句注释掉也行
    //extern int errno;
    FILE*fp = NULL;

    if(NULL ==(fp = fopen("text.t","r")))
    {
        printf("errno = %d\n",errno);
        printf("Mesg:%s\n",strerror(errno));
    }
    return 0;
}
