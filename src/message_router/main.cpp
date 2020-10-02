/**
 *  TODO:
 * 1. initialize outputs (slack, mail, db, etc.)
 * 2. initialize socket file
 * 3. signal handler
 * 4. start loop
 * 5. cleanup everything
*/

#include <csignal>
#include <fstream>

#include <fcntl.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal)
{
    // stop loop, cleanup everything
}

void file_socket(std::string filename)
{
    struct sockaddr_un namesock;
    int fd;
    namesock.sun_family = AF_UNIX;
    strncpy(namesock.sun_path, (char *) filename.c_str(), sizeof(namesock.sun_path));
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(fd, (struct sockaddr *) &namesock, sizeof(struct sockaddr_un));
    close(fd);
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);



    return 0;
}