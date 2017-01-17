#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include <time.h>
pthread_mutex_t rlock;
pthread_mutex_t wlock;
pthread_t rtid;
pthread_t wtid ;
int readcount=0;
int temp=0;
void intialize(){
	srand ( time(NULL)) ;
	pthread_mutex_init(&rlock,NULL);
	
	pthread_mutex_init(&wlock,NULL);
	
	readcount=0;

}

void * reader (void * a){

	int waittime;
	
	waittime = rand() % 5;
	//printf("%d ",waittime);
//	puts ("") ;
	printf("Reader No_%d is trying to enter (-_-)...\n",a);
	
	pthread_mutex_lock(&rlock); // waiting if not unlocked ;
	
	readcount++;
    temp = readcount;
 
	if(readcount==1)
	    pthread_mutex_lock(&wlock);
	
	printf("(^_^)Success, there is/are %d Reader inside\nReader No_%d is entered...\nreadCount = %d\n",readcount, a, readcount);
    if(readcount%4==3){
        printf("meet starvation!\n");
		readcount-=3;
    	printf("readcount = %d\n",readcount);
	    pthread_mutex_unlock(&wlock);
	   //pthread_mutex_lock(&rlock);
	    //pthread_mutex_unlock(&rlock);
	}
	

	pthread_mutex_unlock(&rlock);
	Sleep(waittime);
	pthread_mutex_lock(&rlock);
	if(readcount>=1){
	readcount--;
	printf("readcount = %d\n",readcount);}
    pthread_mutex_unlock(&rlock);

	/*if(readcount>3){
	    Sleep(1000);
	}*/
	
	
//	printf("Reader No_%d is Leaving  ~(^_^)~  \n",a);//會有時間延遲問題 

}

void * writer (void * a){

	int waittime;
	
	waittime=rand() % 3;
	
	printf("Writer No_%d is trying to enter (-_-)...\n",a);

	pthread_mutex_lock(&wlock);
	temp++;
	if(temp==0){pthread_mutex_unlock(&rlock);
	}
	printf("(^_^) Success,Writer No_%d has entered\n",a);
	//pthread_mutex_lock(&rlock);
	Sleep(waittime);
	
	pthread_mutex_unlock(&wlock);
	
	printf("Writer No_%d is leaving (^_^)b\n",a);
	temp--;
	//printf("test3");
	pthread_mutex_lock(&wlock);
	
	pthread_mutex_unlock(&rlock);
	//printf("test4");
	//Sleep(30);
	
	//exit(0);

}

int main(){

	int n1,n2,i;
	
	printf("Enter the number of readers: ");
	
	scanf("%d",& n1);
	
	printf("Enter number of writers: ");
	
	scanf("%d",& n2);
	intialize ();
	
	
	
	for(i=1;i<=n1;i++){
	//	printf ( "READER !!\n") ;
	    pthread_create(&rtid,NULL,reader,(void*)(i));
	}
	
	for(i=1;i<=n2;i++){
	//	printf ( "WRITER !!\n" ) ;
	    pthread_create(&wtid,NULL,writer,(void*)(i));
	}
	Sleep(100);
	printf("Task complete !!!\n");
	
	
	printf("Press any to end:\n");
	
	scanf("%d",&n1);
	
	exit(0);

}
