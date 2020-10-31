#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main() {

	int msqid;
	char pathname[] = "sem.c";
	key_t key;
	int len, maxlen,i;
	int value=0;
	struct mymsgbuf 
	{
		long mtype;
		int operation;		
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

	
		
while(1)
{
	maxlen = sizeof(mybuf);
	if((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0))<0)  {printf("cant rec"); exit(-1);}
	printf("%d %ld \n",mybuf.operation,mybuf.mtype);
if(mybuf.mtype==1)
{		printf("sdfsg");
		
		i=mybuf.operation;
		value=i+value;
		if(value==5)
		{
			
			mybuf.mtype=3;
			len=sizeof(mybuf);
			if(msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) 
			{
				printf("error sending to c1\n");
				exit(-1);
			}	
				
		}
printf(" 1st program : %d \n ",value);
}
if(mybuf.mtype==2)
{
	i=mybuf.operation;
	value=i+value;	
}
		
				
}
	return 0;
}
