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

#include <termios.h>
#include <unistd.h>

/* DATA */

struct termios orig_termios;
char *input;
/* WORDLE */

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void parse_wordlist()
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
        if (iscntrl(c) && c == 'c')
        {
            exit(0);
        }
        else
        {
            printf("%d ('%c')\n", c, c);
        }
    }

    return 0;
}