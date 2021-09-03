#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "assert.h"
#include "uarray2.h"
#include "pnmrdr.h"

//takes the input (either stdin or a file extension) and sets each element of the
//array to the corresponding place in the array
void take_input(UArray2_T array, FILE *source){
	void *read = NULL;
	Pnmrdr_mapdata data;
	int width = 0;
	int height = 0;
	int denominator = 0;

	read = Pnmrdr_new(source);
	data = Pnmrdr_data(read);

	width = data.width;
	height = data.height;
	denominator = data.denominator;

	assert(data.type == Pnmrdr_gray);
	assert(width == 9 && height == 9 && denominator == 9);

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int number = Pnmrdr_get(read);
			int *temp = UArray2_at(&array, i, j);
			*temp = number;
		}
	}


	Pnmrdr_free((Pnmrdr_T *)&read);
}

//Has a blank array that fills in each element it finds in the set of 9 and errors if a repeat is found
void check_solved(UArray2_T array){
	int checkarr[9] = {0,0,0,0,0,0,0,0,0};
	for(int i=0; i<9; i++){
		for(int q=0; q<9; q++){
			checkarr[q] = 0;
		}
		for(int j=0; j<9; j++){
			for(int z=0; z<9; z++){
				//The first checks are each of the rows
				if((intptr_t)UArray2_at(&array, i, j) == checkarr[z]){
					UArray2_free(&array);
					exit(1);
				}
				else {
					if(checkarr[z] == 0){
					       checkarr[z] = (intptr_t)UArray2_at(&array,i,j);
					       break;
					}
				}
			}
		}
	}
	for(int j=0; j<9; j++){
		for(int q=0; q<9; q++){
			checkarr[q]=0;
		}
		for(int i=0; i<9; i++){
			for(int z=0; z<9; z++){
				//The next check are the columns
				if((intptr_t)UArray2_at(&array, i, j) == checkarr[z]){
					UArray2_free(&array);
					exit(1);
				}
				else {
					if(checkarr[z] == 0){
						checkarr[z] = (intptr_t)UArray2_at(&array, i, j);
						break;
					}
				}
			}
		}
	}
	for(int i=0; i<9; i+=3){
		for(int j=0; j<9; j+=3){
			for(int q=0; q<9; q++){
				checkarr[q]=0;
			}
			for(int r=0; r<3; r++){
				for(int c=0; c<3; c++){
					for(int z=0; z<9; z++){
						//Finally it checks the 3x3 areas
						if((intptr_t)UArray2_at(&array, i+r, j+c) == checkarr[z]){
							UArray2_free(&array);
							exit(1);
						}
						else{
							if(checkarr[z] == 0){
								checkarr[z] = (intptr_t)UArray2_at(&array, r+i, c+j);
								break;
							}
						}
					}
				}
			}
		}
	}
}

//calls take_input with the input (either stdin or argv[1]), then calls check_solved. Exits if no error
int main(int argc, char *argv[]){
	FILE *source;
	UArray2_T answer = UArray2_new(9,9, sizeof(int));
	
	assert(argc<=2);

	if(argc == 1){
		source = stdin;
		assert(source != NULL);
	}
	else{
		source = fopen(argv[1], "rb");
		assert(source != NULL);
	}
	take_input(answer, source);
	fclose(source);

	check_solved(answer);
	UArray2_free(&answer);
	exit(0);
}