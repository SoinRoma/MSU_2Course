#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{

	int msqid;
	char pathname[] = "semint.c";
	key_t key;
	int i, len, maxlen;
	
	struct mymsgbuf 
	{
		long mtype;
		int operation;				
	} mybuf;
	
	if((key = ftok(pathname, 0)) < 0) //если не получилось получить ключ
	{
		printf("Can't generate key\n");
		exit(-1);
	}
	

        if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) //если дискриптор отрицательно значение имеет
	{
		printf("Can't get msqd\n");
		exit(-1);
	}
		maxlen = sizeof(mybuf);

	while(1) //цикл. как получит сообщение из очереди. выходит
	{	
		if((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 3, 0))>=0) break;
	}	
	
         mybuf.operation=3;
           mybuf.mtype=2;	
         len=sizeof(mybuf);

        if(msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) //если вдруг нету сообщения в очереди, т.е системный вызов сенд не сработал
        {
	printf("error sending to c1\n");
	exit(-1);
        }
        printf(" im done");

	return 0;
}
