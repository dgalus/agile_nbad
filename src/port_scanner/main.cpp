#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <string>

inline void usage(char* app)
{
    std::cerr << "Usage:\n\t./" << app << " <ip or hostname> <start_port> <end_port> <scan_type>" << std::endl;
    exit(1);
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        usage(argv[0]);
    }
    std::string hostname;
    struct hostent *host;
    int err;
    int i;
    int sock;
    int start;
    int end;

    struct sockaddr_in sa;
    hostname = std::string(argv[1]);

    start = atoi(argv[2]);
    end = atoi(argv[3]);

    strncpy((char*) &sa, "", sizeof(sa));
    sa.sin_family = AF_INET;

    if(isdigit(hostname[0]))
    {
        sa.sin_addr.s_addr = inet_addr(hostname.c_str());
    }
    else if((host = gethostbyname(hostname.c_str())) != 0)
    {
        strncpy((char*) &sa.sin_addr, (char*) host->h_addr, sizeof(sa.sin_addr));
    }
    else
    {
        exit(2);
    }

    for(i = start; i <= end; i++)
    {
        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            exit(3);
        }
        err = connect(sock, (struct sockaddr*) &sa, sizeof(sa));
        if(err < 0)
        {
            fflush(stdout);
        }
        else
        {
            printf("%-5d open\n", i);
            fflush(stdout);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}