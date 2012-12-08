#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
    int    fd;
    fd_set fds;
    char   ch;

    FD_ZERO (&fds);

    fd = open ("/sys/class/gpio/gpio36/value", O_RDWR);
    if (fd == -1) {
       goto out;
    } 

    FD_SET (fd, &fds);

    while (select (fd + 1, NULL, NULL, &fds, NULL) != -1) {
	lseek (fd, 0, SEEK_SET);
        read (fd, &ch, 1);
        printf ("Data is available now (%c).\n", ch);
    }

out:
    perror ("errno set");
    exit (EXIT_SUCCESS);
}
