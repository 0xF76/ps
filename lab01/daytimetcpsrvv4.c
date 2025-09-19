#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include 		<unistd.h>
#include        <time.h>                /* old system? */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>

#define MAXLINE 1024

//#define SA struct sockaddr

#define LISTENQ 2

int
main(int argc, char **argv)
{
    int				    listenfd, connfd, err, n;
    socklen_t			len;
    char				buff[MAXLINE], str[INET_ADDRSTRLEN+1], recvline[MAXLINE + 1];
    time_t				ticks;
    struct sockaddr_in	servaddr, cliaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        fprintf(stderr,"socket error : %s\n", strerror(errno));
        return 1;
    }

    int opt = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        fprintf(stderr,"setsockopt error : %s\n", strerror(errno));
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);	/* daytime server */

    err = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(err < 0) {
        fprintf(stderr,"bind error : %s\n", strerror(errno));
        return 1;
    }

    err = listen(listenfd, LISTENQ);
    if(err < 0) {
        fprintf(stderr,"listen error : %s\n", strerror(errno));
        return 1;
    }

    while(1) {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        if(connfd < 0) {
            fprintf(stderr,"accept error : %s\n", strerror(errno));
            continue;
        }

        memset(str, 0, sizeof(str));
        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str));
        printf("Connection from %s\n", str);

        while(n = read(connfd, recvline, MAXLINE)) {
            recvline[n] = 0;
            err = fputs(recvline, stdout);
            if(err == EOF) {
                fprintf(stderr,"fputs error : %s\n", strerror(errno));
                return 1;
            }
        }
        if(n < 0) {
            fprintf(stderr,"read error : %s\n", strerror(errno));
            return 1;
        }
        
        err = close(connfd);
        if(err < 0) {
            fprintf(stderr,"close error : %s\n", strerror(errno));
            return 1;
        }
    }


 
}
