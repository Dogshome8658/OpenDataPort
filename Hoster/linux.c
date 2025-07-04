#include<unistd.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>


void lprintf(const char* MSG, ...){
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	char time_buf[100];
	size_t rc = strftime(time_buf, sizeof time_buf, "%D %T", gmtime(&ts.tv_sec));
	snprintf(time_buf + rc, sizeof time_buf - rc, ".%06ld UTC", ts.tv_nsec / 1000); //Get the time
	va_list args1;
	va_start(args1, MSG);
	va_list args2;
	va_copy(args2, args1);
	int temp = vsnprintf(NULL, 0, MSG, args1);
	char* buf = (char*)malloc(1 + temp);
	//char buf[1 + vsnprintf(NULL, 0, fmt, args1)];
	va_end(args1);
	vsnprintf(buf,temp+1, MSG, args2);
	va_end(args2);
	//if (GetCurrentThread() == MainThreadHandle) {
		printf("[Thread %lu][%s]: %s\n", pthread_self(), time_buf, buf);
	//}else {
	//	printf("[Thread %x][%s]: %s\n", GetCurrentThreadId(), time_buf, buf);
	//}
}

void lisener(void*psv){
    printf("Might so");
    return;
}

void main(void){
    pthread_t lisener_id=NULL;
    int rtnval=pthread_create(&lisener_id,NULL,lisener,NULL);
    if(rtnval==0){
        printf("CRT Error,%d",__LINE__);
    }
    lprintf("Shall we?");
    return 0;
}