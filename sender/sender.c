#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

int main() {
    const char *portname = "/dev/ttyACM0"; // Cambia esto al puerto serie que esté utilizando tu Arduino
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("No se pudo abrir el puerto serie");
        return 1;
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error al obtener los atributos del puerto");
        close(fd);
        return 1;
    }

    cfsetospeed(&tty, B9600); // Velocidad de transmisión
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 10;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error al establecer los atributos del puerto");
        close(fd);
        return 1;
    }

    char *word = "M"; // La palabra que quieres enviar
    int len = strlen(word);
    if (write(fd, word, len) != len) {
        perror("Error al escribir en el puerto");
        close(fd);
        return 1;
    }else{

        printf("Mensaje enviado: %s\n", word);
    }

    close(fd);
    return 0;
}
