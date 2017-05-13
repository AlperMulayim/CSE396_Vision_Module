#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>

typedef struct 
{
   double rectX;
   double rectY;
   double headCenterX;
   double headCenterY;
   double headRadius;
   double legX;
   double legY;
} package; 

int listenfd = 0, connfd = 0;
struct sockaddr_in serv_addr; 
int param=0;
time_t ticks; 
package package1;
pthread_t socketThread;

void *connection_handler(void *socket_desc);

int main(int argc, char *argv[])
{

    package1.rectX=1;
    package1.rectY=2;
    package1.headCenterX=3;
    package1.headCenterY=4;
    package1.headRadius=5;
    package1.legX=6;
    package1.legY=7;
    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5007); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    
    if(pthread_create(&socketThread,NULL,connection_handler,0) < 0)
    {
        perror("could not create thread");
        return 1;
    }


    while(1)
    {
        printf("asd");
    }
   
}

void *connection_handler(void *socket_desc)
{
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, (void*)&package1, sizeof(package)); 

        sleep(3);
        
        write(connfd, (void*)&package1, sizeof(package));
        
        sleep(3);
        
        write(connfd, (void*)&package1, sizeof(package));
     }
}
