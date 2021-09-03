#include "uarray2.h"
#include "bit.h"
#ifndef BIT2_H_INCLUDED
#define BIT2_H_INCLUDED

#define T Bit2_T
typedef struct T *T;


void Bit2_free(T *array); //Frees the 2D array

int Bit2_get(T array, int row, int col);//gets the value of the bit at [row][col]

int Bit2_put(T array, int row, int col, int bit);//assigns the bit at [row][col] to value bit

int Bit2_width(T array);//returns the width of the array

int Bit2_height(T array);//returns the height of the array

T Bit2_new(int width, int height);//Creates the Bit2 array

void Bit2_map_row_major(T array, void apply(int value, int row, int col, T *array, void *cl), void *cl);
void Bit2_map_col_major(T array, void apply(int value, int row, int col, T *array, void *cl), void *cl);
//Each of these call apply to each value, the order varies with one going full rows first or full columns at a time

#undef T
#endif
