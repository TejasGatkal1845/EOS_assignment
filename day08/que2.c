#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int ret1,ret2,ret3,ret4,ret5,S1,S2,S3,S4,S5;

	ret1 = fork();
	if(ret1 == 0)
	{
		ret2 =fork();
		if(ret2 == 0)
		{
			ret3 =fork();
			if(ret3 == 0)
			{
				ret4 =fork();
				if(ret4 == 0)
				{
					ret5 =fork();
					if(ret5 == 0)
					{
						for(int i =0;i<5;i++)
						{
							printf("5th process is %d and pid is %d",i,getpid());
							sleep(1);
						}
						waitpid(ret5,&S5,0);
						printf("child exit status id %d",WEXITSTATUS(S5));
						
					}
					_exit(0);
					for(int i =0;i<5;i++)
					{
						printf("4th process is %d and pid is %d",i,getpid());
						sleep(1);
					}
					waitpid(ret4,&S4,0);
					printf("child exit status id %d",WEXITSTATUS(S4));
				
				}
				  _exit(0);

				for(int i =0;i<5;i++)
				{
					printf("3rd process is %d and pid is %d",i,getpid());
					sleep(1);
				}
				waitpid(ret3,&S3,0);
				printf("child exit status id %d",WEXITSTATUS(S3));
				
			}
			 _exit(0);

			for(int i =0;i<5;i++)
			{
				printf("2nd process is %d and pid is %d",i,getpid());
				sleep(1);
			}
			waitpid(ret2,&S2,0);
			printf("child exit status id %d",WEXITSTATUS(S2));
			
		}
		_exit(0);
		for(int i =0;i<5;i++)
		{
			printf("1st process is %d and pid is %d",i,getpid());
			sleep(1);
		}
		waitpid(ret1,&S1,0);
		printf("child exit status id %d",WEXITSTATUS(S1));
		
	}
	_exit(0);

	return 0;
}

