#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};
//基本量定义（三种信号量、P操作、V操作、初始化/删除信号量）
static int full;
static int empty;
static int mutex;
static int set_semvalue();
static void del_semvalue();
static int semaphore_p();
static int semaphore_v();
int main(int argc, char *argv[])
{
    int num = 0;
    //创建信号量,利用semget函数
    full = semget((key_t)666, 1, 0666 | IPC_CREAT);
    empty = semget((key_t)777, 1, 0666 | IPC_CREAT);
    mutex = semget((key_t)888, 1, 0666 | IPC_CREAT);
    set_semvalue(full, 0);
    set_semvalue(empty, 5);
    set_semvalue(mutex,  1);
    //初始化信号量，利用semctl函数
    pid_t p1, p2;

    if (p1 = fork())
    {
        while (1)
        {
            semaphore_p(empty);
            semaphore_p(mutex);
            printf("Producer:%d produced a thing, total:%d\n", getpid(), semctl(full, 0, GETVAL, 0) + 1);
            semaphore_v(mutex);
            semaphore_v(full);
            sleep(2);
        }
    }
    else
    {
        if ((p2 = fork()) == 0)
        {
            while (1)
            {
                sleep(2);
                semaphore_p(full);
                semaphore_p(mutex);
                num -= 1;
                printf("Customer:%d used a thing and there is %d things\n", getpid(), semctl(full, 0, GETVAL, 0) + 1);
                semaphore_v(mutex);
                semaphore_v(empty);
                sleep(5);
            }
        }
        else
        {
            while (1)
            {
                sleep(2);
                semaphore_p(full);
                semaphore_p(mutex);
                num -= 1;
                printf("Customer:%d used a thing and there is %d things\n", getpid(), semctl(full, 0, GETVAL, 0) + 1);
                semaphore_v(mutex);
                semaphore_v(empty);
                sleep(5);
            }
        }
    }
}
static int set_semvalue(int sem_id, int n)
{
    //用于初始化信号量，在使用信号量前必须这样做
    union semun sem_union;
    sem_union.val = n;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1){
        printf("error!\n");
        return 0;
    }
        
    return 1;
}
static int semaphore_p(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; //P()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_p failed\n");
        return 0;
    }
    return 1;
}
static int semaphore_v(int sem_id)
{
    //这是一个释放操作，它使信号量变为可用，即发送信号V（sv）
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; //V()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_v failed\n");
        return 0;
    }
    return 1;
}