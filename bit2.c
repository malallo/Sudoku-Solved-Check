#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"
#include "bit.h"
#include "bit2.h"
#include "array.h"
#define T Bit2_T

//Struct for the 2D Array that stores: width and height

struct T {
    int width;
    int height;
    //int size;
    Array_T Array;
};

//Creates a Bit2 array
T Bit2_new(int width, int height){

    //create the 2D array foundation
    Bit2_T mainArray= malloc(sizeof(*mainArray));
    assert(mainArray != NULL);

    //Create the height array that stores the width arrays
    Array_T heightArray = Array_new(height, sizeof(Bit_T));

    for(int i = 0; i < height; i++){
        Bit_T * temp = Array_get(heightArray, i); 
        *temp = Bit_new(width);
    }
    //assign attritbutes to 2D array
    mainArray->width = width;
    mainArray->height = height;
    mainArray->Array = heightArray;

    return mainArray;
}

//Frees the 2D array
void Bit2_free(T *array){
    
    int height = (*array)->height;

    for(int i = 0; i < height; i++){
        Bit_free(Array_get((*array)->Array, i));
    }

    free(array);
}

//gets the value of the bit at (row, col)
int Bit2_get(T array, int row, int col){

    Bit_T *set = Array_get(array->Array, row);
    int gotBit = Bit_get(*set, col);
    
    return gotBit;
}

//assigns the bit at (row, col) the value "bit"
int Bit2_put(T array, int row, int col, int bit){

    
    int oldBit = Bit_get(Array_get(array->Array, row),col);
    Bit_put(Array_get(array->Array, row),col, bit);

    return oldBit;
}

//returns the width of the array
int Bit2_width(T array){
    return array->width;
}

//returns the height of the array
int Bit2_height(T array){
    return array->height;
}


//Each of these functionc call the apply function within on "value",
// the order varies with row major focusing on rows and col major
// on col respectively.
void Bit2_map_row_major(T array, void apply(int value, int row, int col, T *array, void *cl), void *cl){

    int height = array-> height;
    int width = array-> width;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            apply(Bit2_get(array, i, j), i, j, &array, cl);
        }
    }
}

void Bit2_map_col_major(T array, void apply(int value, int row, int col, T *array, void *cl), void *cl){

    int width = array->width;
    int height = array->height;

    for(int j = 0; j < width; j++){
        for(int i = 0; i < height; i++){
            apply(Bit2_get(array, i, j), i, j, &array, cl);
        }
    }
}
