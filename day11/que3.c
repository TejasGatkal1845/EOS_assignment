#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int arr[2];

void sigint_handler(int sig)
{
	close(arr[1]);
	close(arr[0]);
    _exit(0);
}

int main()
{

	char ch = 'M';
	int count = 0,ret;
	ret = pipe(arr);
	if(ret < 0){
		perror("pipe failed\n");
		_exit(1);
	}

	struct sigaction sa;
	// step2: register signal handler
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);

	if(ret < 0) {
		perror("sigaction() failed");
		_exit(1);
	}

	while(1)
	{
		write(arr[1],&ch,sizeof(ch));
		count++;
		printf("bytes written : %d\n",count);
	}

	return 0;
}
