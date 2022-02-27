/**
 * @file forest.h
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

#include <stdlib.h>

#ifndef __FOREST_H__
#define __FOREST_H__

#define DEAD 0
#define ALIVE 1
#define BURNING 2



///Forest automata type.
typedef struct
{
    char** cell;        /**< current generation   */
    char** next;        /**< next generation      */
    size_t width;       /**< width of cell array  */
    size_t height;      /**< height of cell array */
    double burnProb;    /**< probability a tree spontaneously combusts  */
    double growProb;    /**< probability an empty cell grows a new tree */
} forest_t;


///Return a random number between 0 and 1.
double randDouble();



/**
 * @brief Initialize a new forest.
 * 
 * @param width        width of cell array
 * @param height       height of cell array
 * @param burnProb     probability a tree spontaneously combusts
 * @param growProb     probability an empty cell grows a new tree
 * @return forest_t    pointer to the new forest, or NULL if initialization
 *                     failed
 */
forest_t* initForest(size_t width, size_t height, double burnProb, double growProb);



/**
 * @brief Free a forest from memory.
 * 
 * @param f    the target forest
 */
void freeForest(forest_t* f);



/**
 * @brief Print a forest to ncurses stdscr.
 * 
 * @param f    the target forest
 */
void printForest(forest_t* f);



/**
 * @brief Generate the next generation.
 * 
 * @param f    the target forest
 */
void nextGeneration(forest_t* f);



/**
 * @brief 
 * 
 * @param f       the target forest
 * @param x       x position of cell
 * @param y       y position of cell
 * @return int    1 if true, 0 if false
 */
int hasBurningNeighbor(forest_t* f, size_t x, size_t y);



/**
 * @brief Reset a forest to all empty cells.
 * 
 * @param f    the target forest
 */
void clearForest(forest_t* f);



/**
 * @brief Randomly fill a forest with trees.
 * 
 * @param f          the target forest
 * @param density    probability a cell will be set
 */
void randomFill(forest_t* f, double density);

#endif