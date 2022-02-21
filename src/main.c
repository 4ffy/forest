#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "forest.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
    srand(time(NULL));
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //color for dead cells.
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //color for live cells.
    init_pair(3, COLOR_RED,   COLOR_BLACK); //color for burning cells.


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
    
    size_t width    = COLS / 2;
    size_t height   = LINES;

    forest_t* f = initForest(width, height, burnProb, growProb);
    randomFill(f, density);

    while (1)
    {
        printForest(f);
        refresh();
        nextGeneration(f);
        usleep(100000);
    }

    endwin();
    freeForest(f);
    return 0;
}
