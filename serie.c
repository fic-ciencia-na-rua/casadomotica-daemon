#include "util_daemon.h"

int open_port(const char * portoSerie){
	int fd; /*File descriptor for the port */
	
	fd = open(portoSerie, O_RDWR | O_NOCTTY | O_NDELAY );
	printf("abrindo porto serie %s con fd %d\n",portoSerie,fd);
	if (fd == -1){
	/*
	* Could not open the port.
	*/
	    perror("open_port: Unable to open /dev/ttyS0 - ");
	}else
	    fcntl(fd, F_SETFL, 0);
	return fd;
}
/*



*** ESCRIBIR NO PORTO
 n = write(fd, "ATZ\r", 4);
    if (n < 0)
      fputs("write() of 4 bytes failed!\n", stderr);

The write function returns the number of bytes sent or -1 if an error occurred.
Usually the only error you'll run into is EIO  when a MODEM or data link drops
the Data Carrier Detect (DCD) line. This condition will persist until you close the port.








*** LER NO PORTO
Reading data from a port is a little trickier.
When you operate the port in raw data mode, each read(2) system call
will return the number of characters that are actually available in the
serial input buffers. If no characters are available, the call will block (wait)
until characters come in, an interval timer expires, or an error occurs.
The read function can be made to return immediately by doing the following:

    fcntl(fd, F_SETFL, FNDELAY);

The FNDELAY option causes the read function to return 0 if no characters
are available on the port. To restore normal (blocking) behavior,
call fcntl() without the FNDELAY option:

    fcntl(fd, F_SETFL, 0);

This is also used after opening a serial port with the O_NDELAY option.


*** Pechar porto
close(fd);







*/