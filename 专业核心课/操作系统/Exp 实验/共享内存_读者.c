/**
 * 共享内存 ———— 读者
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
	people * p;
	p = (people *)shmat(shem_id,NULL,0);
	printf("name: %s\n\n", p->name);
	printf("age :%d\n\n",p->age);
	shmdt(p);
}
