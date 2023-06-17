/**
 * 共享内存 ———— 写者
 *
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
typedef struct {
	char name[20];
	int age;
}people;
	
int main(){
	key_t key ;
	key = ftok(",",1);
	int shem_id;
	shem_id=shmget(key,getpagesize(),IPC_CREAT|0666);
	printf("%d",shem_id);
	people * p;
	p = (people *)shmat(shem_id,NULL,0);
	char str[] = "zhangJunhua";
	strcpy(p->name, str);
	p->age = 19;
	printf("WRITE SUCCESS\n");
	shmdt(p);
}


