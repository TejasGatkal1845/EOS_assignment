#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
 int signal,pid,ret;

    printf("enter the pid and signal number\n");
    scanf("%d %d",&pid,&signal);


    ret = kill(pid,signal);
	printf("the returned value is %d\n",ret);
  
 return 0;
}
