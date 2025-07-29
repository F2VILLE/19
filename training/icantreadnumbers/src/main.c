#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

char* numtotextarr[100];

void init_numtotext() {
numtotextarr[0] = "zero";
numtotextarr[1] = "one";
numtotextarr[2] = "two";
numtotextarr[3] = "three";
numtotextarr[4] = "four";
numtotextarr[5] = "five";
numtotextarr[6] = "six";
numtotextarr[7] = "seven";
numtotextarr[8] = "eight";
numtotextarr[9] = "nine";
numtotextarr[10] = "ten";
numtotextarr[11] = "eleven";
numtotextarr[12] = "twelve";
numtotextarr[13] = "thirteen";
numtotextarr[14] = "fourteen";
numtotextarr[15] = "fifteen";
numtotextarr[16] = "sixteen";
numtotextarr[17] = "seventeen";
numtotextarr[18] = "eighteen";
numtotextarr[19] = "nineteen";
numtotextarr[20] = "twenty";
numtotextarr[30] = "thirty";
numtotextarr[40] = "fourty";
numtotextarr[50] = "fifty";
numtotextarr[60] = "sixty";
numtotextarr[70] = "seventy";
numtotextarr[80] = "eighty";
numtotextarr[90] = "ninety";
numtotextarr[91] = "hundred";
numtotextarr[92] = "thousand";
numtotextarr[93] = "billion";
numtotextarr[94] = "trillion";
}

//int pow(int a, int exp) {
//  if (exp == 0) return 1;
//  if (exp == 1) return a;
 // int r = a;
//  for (int i = 0; i < exp-1; i++)
//  {
//    r *= a;
//  }
//  return r;
//}

// todo :
// Recursion for unit change    (thousand, billion, ...)
void numtotext(char* txt, int txt_len, char *buffer) {
  int unit = txt_len;
  buffer[0] = '\0';

  for (int i = 0; i < txt_len; i++)
  {
    char c[2] = {0};
    c[0] = txt[i];
    int num = atoi(c);
    if (num == 0 && txt_len > 1) continue;
    char *numtxt = numtotextarr[num*(unit == 2 ? 10 : 1)];
    strcat(buffer, numtxt);
    if (unit > 2)
    {
      strcat(buffer, " ");
      strcat(buffer, numtotextarr[90+(int)floor(txt_len/3)]);
    }
    strcat(buffer, " ");
    unit--;
  }
}

int main(int argc, char* argv[]) {
  init_numtotext();
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }
  char** args = malloc((argc-1)*sizeof(char*));
  int idx = 0;
  for (int i = 1; i < argc; i++)
  {
    int isnum = 1;
    for (int c = 0; c < strlen(argv[i]); c++)
      {
      if (!isdigit(argv[i][c])) {
        isnum = 0;
        break;
      }
    }
    if (isnum)
    {
      args[idx] = argv[i];
      idx++;
    } else {
      printf("'%s' is not a valid number!\n", argv[i]);
    }
  }

  for (int i = 0; i < idx; i++)
  {
    printf("Number : %s\n", args[i]);
    char txtrepr[256]; 
    numtotext(args[i], strlen(args[i]), txtrepr);
    printf("In text : %s\n", txtrepr);
  }

  free(args);
  return 0;
}
