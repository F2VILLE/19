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

/* DATA */

struct termios orig_termios;
char input[6] = {0};
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

void parseWordlist()
{
}

void wordle()
{

}

int main()
{
    
    enableRawMode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        switch (c)
        {
        // backspace
        case 127:
            if (strlen(input) > 0)
            {
                input[strlen(input) - 1] = '\0';
            }
            printf("%s\n", input);

            break;

        case 'c':
            if (iscntrl(c))
            {
                exit(0);
                break;
            }
        default:
            if (
                (c >= 'A' && c <= 'Z') ||
                (c >= 'a' && c <= 'z'))
            {
                if (strlen(input) < 5)
                {
                    input[strlen(input)] = (c >= 'a' && c <= 'z') ? (c - 'a') + 'A' : c;
                    input[strlen(input) + 1] = '\0';
                }
                printf("%s\n", input);
            }
        }
        wordle();
    }

    return 0;
}