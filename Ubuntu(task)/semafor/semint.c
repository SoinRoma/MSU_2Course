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
	int value=0;
	struct mymsgbuf 
	{
		long mtype; //тип сообщения
		int operation; //информация сообщени
	} mybuf;
	
	if((key = ftok(pathname, 0)) < 0) //если не получилось сгенирировать ключ
	{
		printf("Can't generate key\n");
		exit(-1);
	}
        if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)   //если дискриптор имеет отрицательное значение
	{
		printf("Can't get msqd\n");
		exit(-1);
	}

	mybuf.mtype=1; //тип собщения =1
	mybuf.operation=1;
        len=sizeof(mybuf);
	if(msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) //если не получилось поместить сообщение в очередь
        {
		printf("error sending to c1\n");
		exit(-1);
	}
	
			

	return 0;
}
