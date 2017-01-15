
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

pthread_mutex_t rlock;
pthread_mutex_t wlock;
pthread_mutex_t slock;
pthread_t tid;
int readcount;
//int starvationflag;


void intialize(){

    pthread_mutex_init(&rlock,NULL);

    pthread_mutex_init(&wlock,NULL);

    //pthread_mutex_init(&slock,NULL);

    readcount=0;
//starvationflag=0;

}

void * reader (void * a){

    int waittime;

    waittime = rand() %5 ;
   // Sleep(waittime);

    printf("\nReader No_%d is trying to enter (-_-)...",a);

//if(starvationflag==0){

    pthread_mutex_lock(&rlock);
//pthread_mutex_lock(&slock);

    readcount++;

    if(readcount==1){

        pthread_mutex_lock(&wlock);
    }


    printf("\n(^_^) Success, there is/are %d Reader inside",readcount);

/*if(readcount==3){
    //starvationflag=1;
    printf("\nMeet Starvation!");
    pthread_mutex_lock(&slock);
    //pthread_mutex_lock(&rlock);
    // printf("LOCK!");
    pthread_mutex_unlock(&rlock);
    Sleep(waittime);

    pthread_mutex_lock(&rlock);
    //pthread_mutex_lock(&slock);

    readcount--;
    pthread_mutex_unlock(&rlock);
    pthread_mutex_unlock(&slock);

    printf("\nReader No_%d is Leaving  ~(^_^)~  ",a);

}*/

    pthread_mutex_unlock(&rlock);
//pthread_mutex_unlock(&slock);
//pthread_mutex_lock(&slock);

    Sleep(waittime);

    pthread_mutex_lock(&rlock);
//pthread_mutex_lock(&slock);

    readcount--;


    if(readcount==0){
        pthread_mutex_unlock(&wlock);
    //pthread_mutex_unlock(&slock);
    }

    pthread_mutex_unlock(&rlock);
//pthread_mutex_unlock(&slock);

    printf("\nReader No_%d is Leaving  ~(^_^)~  ",a);
//}
}

void * writer (void * a){

    int waittime;

    waittime=rand() % 3;

    printf("\nWriter No_%d is trying to enter (-_-)...",a);

    pthread_mutex_lock(&wlock);


    printf("\n(^_^) Success,Writer No_%d has entered",a);

    Sleep(waittime);

    pthread_mutex_unlock(&wlock);
//starvationflag=0;
    printf("\nWriter No_%d is leaving (^_^)b",a);
    pthread_mutex_lock(&wlock);
    //pthread_mutex_unlock(&slock);
//pthread_mutex_unlock(&slock);
//Sleep(30);
//exit(0);
}

int main(){
    int n1,n2,i;
    printf("Enter the number of readers: ");
    scanf("%d",&n1);
    printf("Enter the number of writers: ");
    scanf("%d",&n2);
    intialize();

    for(i=0;i<n1;i++){
        pthread_create(&tid,NULL,reader,(void*)i+1);
    }
        for(i=0;i<n2;i++){
        pthread_create(&tid,NULL,writer,(void*)i+1);
    }

    Sleep(500*i);
    printf("\nTask complete !!!");
    printf("\nPress any to end:");
    scanf("%d",&n1);
    exit(0);
}
