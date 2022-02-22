# Forest Fire

Forest fire cellular automata, using ncurses.

The automata follows four simple rules. Each generation:
1. Each empty cell has some probability *p* of growing a new tree.
2. Each tree has some probability *f* of catching on fire.
3. A tree that neighbors a burning tree will catch on fire.
4. A burning tree will become an empty cell.

The cell grid is automatically sized to the terminal. Each cell is two block characters wide for a squarish appearance. Wide characters in C are odd so I'm not sure how this will look if some weird locale is used. The animation runs at roughly 10 frames per second via usleep(), and exits when a key is pressed.

The program is passed the starting density, *f*, and *p* in that order. Here's a starting value that looks good to me.  
```./forest 0.5 0.00001 0.001```
