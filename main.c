// main.c
#include <stdio.h>
#include "biblioteca.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <message>\n", argv[0]);
    return 1;
  }

  send_serial(argv[1]);
  return 0;
}
