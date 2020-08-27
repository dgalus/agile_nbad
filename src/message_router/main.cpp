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

void signal_handler(int signal)
{
    // stop loop, cleanup everything
}



int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);



    return 0;
}