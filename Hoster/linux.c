#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

void lisener(void*psv){
    printf("Might so");
    return;
}

void main(void){
    pthread_t lisener_id=NULL;
    pthread_create(&lisener_id,NULL,&lisener,NULL);
    printf("Shall we?");
    return 0;
}