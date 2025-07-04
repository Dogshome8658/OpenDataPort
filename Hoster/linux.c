#include<unistd.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>

#define SOCKET int

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
		printf("[Thread %lx][%s]:%s\n", pthread_self(), time_buf, buf);
	//}else {
	//	printf("[Thread %x][%s]: %s\n", GetCurrentThreadId(), time_buf, buf);
	//}
    return;
}

void bell(void){
    printf("\a");
    return;
}

void lisener(void*psv){
    lprintf("Hereby the lisener");
    return;
}

void main(void){
    lprintf("OpenDataPort INDEV0.1\a");
    lprintf("For any issue please report to the repositry");
    int rtnval=0;

    SOCKET lisener_socket=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in hoster_position;
    memset(&hoster_position,0,sizeof(hoster_position));
    hoster_position.sin_family=AF_INET;
    hoster_position.sin_port=htons(25015);
    //hoster_position.sin_addr.s_addr=htonl("localhost");
    hoster_position.sin_addr.s_addr=htonl(INADDR_ANY);
    //rtnval=bind(lisener_socket,(struct sockaddr *)&lisener_socket,sizeof(struct sockaddr_in));
    rtnval=bind(lisener_socket,(struct sockaddr *)&lisener_socket,sizeof(lisener_socket));
    if (rtnval!=0){
        lprintf("Failed to prepare lisener\'s depedency!Yet the reply is %d\a",rtnval);
        lprintf("And in detail is %d",errno);
        abort();
    }
    lprintf("Prepared lisener\'s depedency");

    pthread_t lisener_id=NULL;
    rtnval=pthread_create(&lisener_id,NULL,lisener,NULL);
    if(rtnval!=0){
        lprintf("Failed to create lisener!,yet the reply is %d\a",rtnval);
        lprintf("And in detail is %d",errno);
        abort();
    }
    sleep(1);
    return 0;
}