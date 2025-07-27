#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

void commandHandler(char *inp) {
    if (strcmp(inp, "exit") == 0) exit(0);
    else if (strcmp(inp, "cat") == 0) {
        printf("meow !\n");
    }
    else {
        printf("Command not found!\n");
    }
}

void loop() {
  char inp[256] = {0};
  while (fgets(inp, 256, stdin) != NULL)
  {
    
    for (int i = 0; i < sizeof(inp); i++) {
      if (inp[i] == '\0') {
        inp[i-1] = '\0';
        break;
      }
    }
    //printf("Input : %s\n", inp);
    commandHandler(inp);
    printf("$>");
  }
}

int main() {
  printf("$>");
  loop();
  return 0;
}
