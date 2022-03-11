/**
 * @file main.c
 * @author Cameron Norton
 * @copyright Copyright (c) 2022 Cameron Norton
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "forest.h"

int main(int argc, char** argv)
{
    //Setup.
	setlocale(LC_ALL, "");
    srand(time(NULL));
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //color for dead cells.
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //color for live cells.
    init_pair(3, COLOR_RED,   COLOR_BLACK); //color for burning cells.

    //Basic argument parsing.
	double density  = 0;
	double burnProb = 0;
	double growProb = 0;
	if (argc == 4)
	{
    	density  = atof(argv[1]);
    	burnProb = atof(argv[2]);
    	growProb = atof(argv[3]);
    }
    if (!density || !burnProb || !growProb)
    {
    	fprintf(stderr, "Usage: %s density burnprob growprob\n\n", argv[0]);
    	endwin();
    	return 1;
    }
    
    //Setup forest.
    size_t width    = COLS / 2;
    size_t height   = LINES;
    forest_t* f = initForest(width, height, burnProb, growProb);
    randomFill(f, density);

    //Run the automata until a key is pressed.
    while (1)
    {
        printForest(f);
        refresh();
        nextGeneration(f);
        usleep(100000);
        if (getch() != ERR) break;
    }

    //End.
    endwin();
    freeForest(f);
    return 0;
}
