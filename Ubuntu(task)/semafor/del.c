
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {

	int msqid;
	char pathname[] = "semint.c";
	key_t key;
	int i, len, maxlen;
	
	struct mymsgbuf 
	{
	
	int value;	
	long type;		
	} mybuf;
	
	if((key = ftok(pathname, 0)) < 0) 
	{
		printf("Can't generate key\n");
		exit(-1);
	}
	

	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) 
	{
		printf("Can't get msqd\n");
		exit(-1);
	}
                

if(msgctl(msqid,IPC_RMID,NULL) < 0) {
		printf("error sending to c1\n");
		
		exit(-1);
	}
printf("succsess");
return 0;
}
