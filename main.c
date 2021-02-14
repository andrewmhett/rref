#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

void draw_matrix(float ** matrix, int rows, int cols){
	for (int o=0;o<cols-1;o++){
		char col_label;
		switch(o){
			case 0:
				col_label='x';
				break;
			case 1:
				col_label='y';
				break;
			case 2:
				col_label='z';
				break;
			default:
				col_label=97+(o-2);
				break;
		}
		printf("%-*c",7,col_label);
	}
	printf("%-*s",7,"const");
	printf("\n");
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			if ((int)(100*matrix[i][o]) == 0){
				printf("0      ");
			}else{
				printf("%-*.2G",7,matrix[i][o]);
			}
		}
		printf("\n");
	}
}



void rref_matrix(float ** matrix, int rows, int cols){
	for (int i=0;i<rows;i++){
		if (i==cols-1){
			break;
		}
		if (matrix[i][i] == 0){
			for (int z=0;z<rows;z++){
				if (z != i){
					if (matrix[z][i] != 0){
						swap_rows(matrix, z, i);
						printf("R%d <-> R%d\n", i+1, z+1);
						draw_matrix(matrix, rows, cols);
						break;
					}
				}
			}
		}
		if (matrix[i][i] != 1){
			printf("R%d / %.2f\n", i+1, matrix[i][i]);
			normalize_row(matrix, i, cols);
			draw_matrix(matrix, rows, cols);
		}
		for (int z=0;z<rows;z++){
			if (z != i){
				if (matrix[z][i] != 0){
					if (matrix[z][i]<0){
						printf("R%d + %.2f * R%d\n", z+1, -1*matrix[z][i], i+1);
					}else{
						printf("R%d - %.2f * R%d\n", z+1, matrix[z][i], i+1);
					}
					float buffer[cols];
					for (int o=0;o<cols;o++){
						buffer[o] = matrix[z][o];
					}
					for (int o=0;o<cols;o++){
						matrix[z][o] -= (buffer[i]*matrix[i][o]);
					}
					draw_matrix(matrix, rows, cols);
				}	
			}
		}
	}
	for (int i=0;i<rows;i++){
		int zero_row = 1;
		for (int o=0;o<cols-1;o++){
			if (matrix[i][o] != 0){
				zero_row = 0;
			}
		}
		if (zero_row && matrix[i][cols-1] != 0){
			printf("No solutions. The matrix is inconsistent.\n");
			return;
		}
	}
	printf("--SOLUTIONS--\n");
	char col_labels[cols-1];
	for (int o=0;o<cols-1;o++){
		char col_label;
		switch(o){
			case 0:
				col_label='x';
				break;
			case 1:
				col_label='y';
				break;
			case 2:
				col_label='z';
				break;
			default:
				col_label=97+(o-2);
				break;
		}
		col_labels[o] = col_label;
	}
	for (int o=0;o<cols-1;o++){
		printf("%c = %G", col_labels[o], matrix[o][cols-1]);
		for (int i=o+1;i<cols-1;i++){
			if (matrix[o][i] != 0){
				if (matrix[o][i]<0){
					printf(" + %.2G%c",matrix[o][i],col_labels[o]);
				}else{
					printf(" - %.2G%c",matrix[o][i],col_labels[o]);
				}
			}
		}
		printf("\n");
	}
}

int main(){
	printf("RREF Solver\nHow many rows? ");
	int rows = 0, cols = 0;
	scanf("%d", &rows);
	printf("How many columns? ");
	scanf("%d", &cols);
	printf("Solving for %dx%d matrix...\n",rows,cols);
	float ** matrix_array = malloc(rows*sizeof(float*));
	for (int i=0;i<rows;i++){
		matrix_array[i] = malloc(cols*sizeof(float));
	}
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			printf("Row %d, Column %d: ",i+1,o+1);
			scanf("%f", &matrix_array[i][o]);
		}
	}
	printf("INITIAL MATRIX\n");
	draw_matrix(matrix_array, rows, cols);
	rref_matrix(matrix_array, rows, cols);
	free(matrix_array);
	return 0;
}
