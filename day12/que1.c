#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// p1 -- writer
int main() {
	int fd1,fd2,num1,num2,res;
	
	fd1 = open("/tmp/desd_fifo", O_WRONLY);
	if(fd1 < 0) {
		perror("open() failed");
		_exit(1);
	}

	printf("enter a two numbers num1 and num2 : \n");
	scanf("%d %d",&num1,&num2);

	 write(fd1, &num1, sizeof(num1));
	 write(fd1, &num2, sizeof(num2));

	 fd2 = open("/tmp/desd_fifo", O_RDONLY);
      if(fd2 < 0) {
          perror("open() failed");
          _exit(1);
      }


     read(fd2,&res,sizeof(res));
	 printf("sum is %d\n",res);
	//printf("written in fifo: %d %d bytes\n", cnt,cnt1);

	close(fd1);
	close(fd2);
	return 0;
}

