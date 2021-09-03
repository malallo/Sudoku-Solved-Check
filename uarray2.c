#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"
#include "array.h"
#include "uarray2.h"
#define T UArray2_T

struct T{
	int width;
	int height;
	int size;
	Array_T Array;
};

//Creates a new 2D array using width and height instead of length, including the size attributw
T UArray2_new(int width, int height, int size){
	assert(width!=0 && height!=0);
	assert(size!=0);

	UArray2_T ArrayOut = malloc(sizeof(*ArrayOut));
	assert(ArrayOut!=NULL);
	Array_T arr = Array_new(height, size);
	for(int i = 0; i < height; i++){
		Array_T *temp = Array_get(arr, i);
		Array_T inner = Array_new(width, size);
		*temp = inner;
	}
	ArrayOut->width = width;
	ArrayOut->height = height;
	ArrayOut->size = size;
	ArrayOut->Array = arr;
	return ArrayOut;
}

//Frees the memory allocated with each of the inner arrays then the array of arrays
void UArray2_free(T *array){
	assert(array!=NULL && *array!=NULL);
	for (int i=0; i<((*array)->height); i++){
		Array_free(Array_get((*array)->Array, i));
	}
	Array_free(&((*array)->Array));
	free(*array);
}

//Finds the position of an element within the 2D arrays
void *UArray2_at(T *array, int row, int col){
	
	void *tmp = Array_get(Array_get((*array)->Array, row), col);
	return tmp;
}

//Finds the width of a specific inner array
int UArray2_width(T array){

	return array->width;
}

//Finds the height of the 2D array
int UArray2_height(T array){
	return array->height;
}

//Finds the data size of each inner array within the 2D array
int UArray2_size(T array){
	return array->size;
}

//Takes the array in question and uses the apply function on each element by going through 
// a full row at a time.
void UArray2_map_row_major(T array, void apply(void *value, int row, int col, T *array, void *cl), void *cl){
	int width = array->width;
	int height = array->height;
	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){
			apply(UArray2_at(&array, i, j), i, j, &array, cl);
		}
	}
}

//Takes the array in question and uses the apply function on each element by going through 
// a full column at a time.
void UArray2_map_col_major(T array, void apply(void *value, int row, int col, T *array, void *cl), void *cl){
	int width = array->width;
	int height = array->height;
	for (int j=0; j<width; j++){
		for (int i=0; i<height; i++){
			apply(UArray2_at(&array, i, j), i, j, &array, cl);
		}
	}
}

#undef T