/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: F2Ville <contact@f2ville.dev>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 03:19:31 by F2Ville           #+#    #+#             */
/*   Updated: 2025/07/25 03:19:31 by F2Ville          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* IMPORTS */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
/* DATA */

struct termios orig_termios;
char guessword[6] = {0}; 
char input[6] = {0};
int tries = 0;

/* WORDLE */

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void getRandomWord()
{
  FILE *words_file = fopen("wordlist.txt", "r");

  if (words_file == NULL)
  {
    printf("wordlist.txt not found");
    exit(1);
  }
  char *line = NULL;
  int i = 0;
  size_t len = 0;
  ssize_t read;
  int t = rand() % 100;
  while (read = getline(&line, &len, words_file) != -1)
  {
    if (i == t) {
      for (int j = 0; j < 5; j++)
      {
        guessword[j] = (line[j] - 'a') + 'A';
      }
      guessword[6] = '\0';
      break;
    }
    i++;
  }  
}

void wordle()
{
  char output[256] = {0};
  char lettersleft[6] = {0};
  strcpy(lettersleft, guessword);
  gotoxy(2, 5);
  int pos = 0;
  for (int i = 0; i < 5; i++)
  {
    gotoxy(2, 12+i);
    bool available = false;
    for (int j = 0; j<5; j++)
    {
      if (input[i] == lettersleft[j])
      {
        available = true;
        lettersleft[j] = '-';
      }
    }

    if (!available) {
      pos += sprintf(output + pos, "\033[0m%c", input[i]);
      continue;
    }

    if (input[i] == guessword[i]) {
      pos += sprintf(output + pos, "\033[92m%c\033[0m", input[i]);
    } else
    {
      bool found = false;
      for (int j = 0; j < 5; j++)
      {
        if (input[i] == guessword[j]) {
          pos += sprintf(output + pos, "\033[93m%c\033[0m", input[i]);
          found = true;
          break;
        }
      }
      if (!found)
      {
        pos += sprintf(output + pos, "\033[0m%c", input[i]);
      } 
    }

  }
  gotoxy(0, tries + 2);
  printf("%d] %s             \n", tries+1, output);
  tries++;
  bool win = true;
  for (int i = 0; i < 5; i++)
  {
    if (input[i] != guessword[i]) win = false;
  }

  if (win) {
    gotoxy(1, 7);
    printf("Congrats! You guessed the workd '%s' in %d tries\n", guessword, tries);
    exit(0);
  }

  if (tries == 5) {
    gotoxy(1, 7);
    printf("You lose! The word was '%s'\n", guessword);
    exit(1);
  }
  bzero(input, 6);
}

int main()
{
    srand(time(NULL));
    getRandomWord();

    clear();
    printf("\033[96mWelcome to WORDLE\033[0m (press ENTER to start)\n");
    gotoxy(2, 15);
    printf("\033[92mLetter in word and in the right position");
    gotoxy(2, 16);
    printf("\033[93mLetter in word but wrong position\033[0m");
    gotoxy(0,2);
    enableRawMode();     

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        gotoxy(0, tries + 2);
        switch (c)
        {
        case 127: // return
            if (strlen(input) > 0)
            {
                input[strlen(input) - 1] = '\0';
            }
            break;
        case 10: // enter
          if (strlen(input) >= 5) {
            wordle();
          }
          break;
        case 'c':
            if (iscntrl(c))
            {
                exit(0);
            }
        default:
            if (strlen(input) < 5 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ) {
                input[strlen(input)] = c >= 'a' && c <= 'z' ? 'A' + (c-'a') : c;
                input[strlen(input) + 1] = '\0';
            }

        }
        printf("%d] %s               \n", tries+1, input);

    }

    return 0;
}
