#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// p2 -- reader
int main() {
	int fd1,fd2, cnt,res,num1,num2;
	char str[32];
	fd1 = open("/tmp/desd_fifo", O_RDONLY);
	if(fd1 < 0) {
		perror("open() failed");
		_exit(1);
	}

	 printf("waiting for data...\n");
	 read(fd1, &num1, sizeof(num1));
	 read(fd1, &num2, sizeof(num2));

	 res = num1 + num2;

	 fd2 = open("/tmp/desd_fifo", O_WRONLY);
     if(fd2 < 0) {
         perror("open() failed");
         _exit(1);
     }

	
	 write(fd2,&res,sizeof(res));
	// printf("the result is %d",res);
	 //printf("read from fifo: %d bytes \n", cnt);

	close(fd1);
	close(fd2);
	return 0;
}


