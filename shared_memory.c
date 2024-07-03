//USER_1
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct memory
{
    int serverup;
    int clientup;
    int rw;
    char msg[100];
};
struct memory *shmptr;
int main()
{
    int shmid;
    shmid=shmget(566,sizeof(struct memory),IPC_CREAT|0666);
    shmptr=(struct memory*)shmat(shmid,NULL,0);
    shmptr->rw=0;
    while(1)
    {
        while(shmptr->rw!=1);
        while(shmptr->clientup==0)
        {
            printf("Message from user2: ");
            if(strcmp(shmptr->msg,"stop")==0)
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->serverup=0;
            shmptr->clientup=1;
            }
            printf("User 1:");
            if(strcmp(shmptr->msg,"stop")==0)
            {
                exit(1);
            }
            else
            {
                fgets(shmptr->msg,100,stdin);
                shmptr->msg[strcspn(shmptr->msg,"\n")]='\0';
            }
            shmptr->rw=0;
        }
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
    }
//USER_2
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct memory
{
    int serverup;
    int clientup;
    int rw;
    char msg[100];
};
struct memory *shmptr;
int main()
{
    int shmid;
    shmid=shmget(566,sizeof(struct memory),IPC_CREAT|0666);
    shmptr=(struct memory*)shmat(shmid,NULL,0);
    shmptr->rw=0;
    while(1)
    {
        while(shmptr->rw=1);
        while(shmptr->clientup==1)
        {
            printf("Message from user1: ");
            if(strcmp(shmptr->msg,"stop")==0)
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->serverup=1;
            shmptr->clientup=0;
        }
        printf("User2: ");
        if(strcmp(shmptr->msg,"stop")==0)
        {
            exit(1);
        }
        else
        {
            fgets(shmptr->msg,100,stdin);
            shmptr->msg[strcspn(shmptr->msg,"\n")]=='\0';
        }
        shmptr->rw=1;
    }
        shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
