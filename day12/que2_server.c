#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

int serv_fd;

void sigint_handler(int sig){

	shutdown(serv_fd, SHUT_RDWR);
	unlink("/tmp/desd_socket");
	_exit(0);
}

// server
#define SERV_PORT	2809
#define SERV_IP		"127.0.0.1"
int main() {
	int  cli_fd, ret,res,num1,num2;
	struct sockaddr_un serv_addr, cli_addr;
	socklen_t socklen;
	struct sigaction sa;

	memset(&sa,0,sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT,&sa,NULL);

	serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(serv_fd < 0) {
		perror("socket() failed");
		_exit(1);
	}

	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path , "/tmp/desd_socket");
	//	inet_aton(SERV_IP, &serv_addr.sin_addr);
	ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0) {
		perror("bind() failed");
		_exit(2);
	}

	listen(serv_fd, 5);

	socklen = sizeof(cli_addr);
	while(1){
		cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
		if(cli_fd < 0) {
			perror("accept() failed");
			_exit(3);
		}


		read(cli_fd, &num1, sizeof(num1));
		printf("client: %d\n", num1);

		read(cli_fd, &num2, sizeof(num2));
		printf("client: %d\n", num2);


		//	printf("server: ");
		res = num1 + num2;

		write(cli_fd, &res, sizeof(res));


		close(cli_fd);
	}

	return 0;
}

