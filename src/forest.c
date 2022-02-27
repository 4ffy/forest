/**
 * @file forest.c
 * @author 4ffy
 * @copyright Copyright (c) 2022 4ffy
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

#define _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include "forest.h"



double randDouble()
{
    return (double) rand() / RAND_MAX;
}



forest_t* initForest(size_t width, size_t height, double burnProb, double growProb)
{
    forest_t* f = malloc(sizeof(forest_t));

    f->cell = malloc(width * sizeof(char*));
    f->next = malloc(width * sizeof(char*));
    for (size_t x = 0; x < width; x++)
    {
        f->cell[x] = calloc(height, sizeof(char));
        f->next[x] = calloc(height, sizeof(char));
    }

    f->width    = width;
    f->height   = height;
    f->burnProb = burnProb;
    f->growProb = growProb;

    return f;
}



void freeForest(forest_t* f)
{
    if (f)
    {
        for (size_t x = 0; x < f->width; x++)
        {
            free(f->cell[x]);
            free(f->next[x]);
        }

        free(f->cell);
        free(f->next);

        free(f);
    }
}



void printForest(forest_t* f)
{
    for (size_t y = 0; y < f->height; y++)
    {
        for (size_t x = 0; x < f->width; x++)
        {
            switch (f->cell[x][y])
            {
                case DEAD:
                attron(COLOR_PAIR(1));
                mvaddwstr(y, 2 * x, L"  ");
                attroff(COLOR_PAIR(1));
                break;

                case ALIVE:
                attron(COLOR_PAIR(2));
                mvaddwstr(y, 2 * x, L"██");
                attroff(COLOR_PAIR(2));
                break;

                case BURNING:
                attron(COLOR_PAIR(3));
                mvaddwstr(y, 2 * x, L"██");
                attroff(COLOR_PAIR(3));
                break;
            }
        }
    }
}



void nextGeneration(forest_t* f)
{
    //Generate next generation.
    for (size_t x = 0; x < f->width; x++)
    {
        for (size_t y = 0; y < f->height; y++)
        {
            switch(f->cell[x][y])
            {
                case DEAD:
                f->next[x][y] = (randDouble() < f->growProb) ? ALIVE : DEAD;
                break;

                case ALIVE:
                if (randDouble() < f->burnProb || hasBurningNeighbor(f, x, y))
                    f->next[x][y] = BURNING;
                else
                    f->next[x][y] = ALIVE;
                break;

                case BURNING:
                f->next[x][y] = DEAD;
                break;
            }
        }
    }

    //Copy next generation to current generation.
    for(size_t x = 0; x < f->width; x++)
        for (size_t y = 0; y < f->height; y++)
            f->cell[x][y] = f->next[x][y];
}



int hasBurningNeighbor(forest_t* f, size_t x, size_t y)
{
    if (x > 0)
    {
        if (f->cell[x-1][y] == BURNING) return 1;

        if (y > 0)
        {
            if (f->cell[x]  [y-1] == BURNING) return 1;
            if (f->cell[x-1][y-1] == BURNING) return 1;
        }

        if (y < f->height - 1)
        {
            if (f->cell[x]  [y+1] == BURNING) return 1;
            if (f->cell[x-1][y+1] == BURNING) return 1;
        }
    }

    if (x < f->width - 1)
    {
        if (f->cell[x+1][y] == BURNING)                          return 1;
        if (y > 0 && (f->cell[x+1][y-1] == BURNING))             return 1;
        if (y < f->height - 1 && (f->cell[x+1][y+1] == BURNING)) return 1;
    }

    return 0;
}



void clearForest(forest_t* f)
{
    for (size_t x = 0; x < f->width; x++)
    {
        for (size_t y = 0; y < f->height; y++)
        {
            f->cell[x][y] = DEAD;
            f->next[x][y] = DEAD;
        }
    }

}



void randomFill(forest_t* f, double density)
{
    for (size_t x = 0; x < f->width; x++)
        for (size_t y = 0; y < f->height; y++)
            f->cell[x][y] = (randDouble() < density) ? ALIVE : DEAD;
}
