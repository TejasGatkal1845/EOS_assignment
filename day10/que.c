#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY		0x1234

typedef struct msg {
	long type;
	int num1,num2;
} msg_t;

typedef struct msg1{
	long type;
	int res;
} msg_t1;

int main() {
	int mqid, ret, s;
	// create message queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0) {
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0) {
		// child: initialize and send the message
		msg_t m1;
		msg_t1 m3;
		m1.type = 1;
		printf("sender: enter a num1 & num2: ");
		scanf("%d %d", &m1.num1,&m1.num2);
		ret = msgsnd(mqid, &m1, 8, 0);
		printf("sender: message sent: %d\n", ret);
		ret = msgrcv(mqid,&m3,4,2,0);
	    printf("result received %d\n",m3.res);
	}
	else {
		// parent: receive the message and print it
		msg_t m2;
		msg_t1 m4;
		m4.type = 2;
		printf("receiver: waiting for the message...\n");
		ret = msgrcv(mqid, &m2, 8, 1, 0);
		printf("receiver: message received: %d -- %d %d\n", ret, m2.num1,m2.num2);
		m4.res = m2.num1 + m2.num2;
		ret = msgsnd(mqid,&m4,4,0);
		printf("result send %d\n",ret);

	
		// wait for child and clean it up
		wait(&s);

		// destroy the message queue
		msgctl(mqid, IPC_RMID, NULL);
	}
	return 0;
}








