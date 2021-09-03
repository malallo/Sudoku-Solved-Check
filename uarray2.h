#include <array.h>
#ifndef UARRAY_INCLUDED
#define UARRAY_INCLUDED

#define T UArray2_T
typedef struct T *T;

void UArray2_free(T *array); //Frees the 2D array

void *UArray2_at(T *array, int row, int col);//Like Hanson's array get except for 2 dimensions at [row][col]

int UArray2_width(T array);//returns the width of the array

int UArray2_height(T array);//returns the height of the array

int UArray2_size(T array);//returns the amount of bytes an index can hold

T UArray2_new(int width, int height, int size);//Creates the UArray2

void UArray2_map_row_major(T array, void apply(void *value, int row, int col, T *array, void *cl), void *cl);
void UArray2_map_col_major(T array, void apply(void *value, int row, int col, T *array, void *cl), void *cl);

#undef T
#endif
