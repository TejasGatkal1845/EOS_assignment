#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int res,s,i=1;
	printf("program starts..");
	while(1)
	{
		res =fork();
		if(res == 0)
		{
			printf("child process is created %d",getpid());
			_exit(0);
		}

		else if(res == -1)
		{
			printf("progam failed");
			break;
		}

		else
		{
			i++;
			printf("parent count %d \n",i);
		}
	}
	for(int j =0;j<i;j++)
	 wait(&s);
	
}
