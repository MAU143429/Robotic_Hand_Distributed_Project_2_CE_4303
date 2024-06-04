#include <stdio.h>
#include <fcntl.h>  // for open function and file control flags
#include <unistd.h>  // for O_RDWR, O_NOCTTY, and O_NDELAY constants
#include <termios.h>
#include <string.h>

void send_serial(const char *message) {
  int fd;
  struct termios options;

  // Open the serial port
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd < 0) {
    perror("open");
    return;
  }

  // Configure the serial port settings
  tcgetattr(fd, &options);
  options.c_cflag = B9600 | CS8 | PARENB | INPCK;
  options.c_iflag = IGNPAR | IGNBRK;
  options.c_oflag = OPOST;
  options.c_lflag = ICANON | ECHO | ECHOE | ECHOK;
  tcsetattr(fd, TCSANOW, &options);

  // Write the string to the serial port
  int bytes_written = write(fd, message, strlen(message));
  if (bytes_written < 0) {
    perror("write");
  }

  // Close the serial port
  close(fd);
}
