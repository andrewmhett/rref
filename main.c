#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

void draw_matrix(float ** matrix, int rows, int cols){
	int col_widths[cols];
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			col_widths[o]=0;
			char str_value[20];
			sprintf(str_value, "%.2f", matrix[i][o]);
			if ((int)strlen(str_value)>col_widths[o]){
				col_widths[o]=(int)strlen(str_value);
			}
		}
	}
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			char str_value[20];
			sprintf(str_value, "%.2f", matrix[i][o]);
			printf("%.2f",matrix[i][o]);
			for (int n=-1;n<col_widths[o]-(int)strlen(str_value);n++){
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("--------\n");
}



void rref_matrix(float ** matrix, int rows, int cols){
	for (int i=0;i<rows;i++){
		if (matrix[i][0] != 0){
			if (i == 0){
				break;
			}else{
				swap_rows(matrix, i, 0);
				printf("R%d <-> R1\n", i+1);
				draw_matrix(matrix, rows, cols);
				break;
			}
		}
	}
	if (matrix[0][0] != 1){
		printf("R1 / %.2f\n", matrix[0][0]);
		normalize_row(matrix, 0, cols);
		draw_matrix(matrix, rows, cols);
	}
	for (int i=1;i<rows;i++){
		if (matrix[i][0] != 0){
			printf("R%d - %.2f * R1\n", i+1, matrix[i][0]);
			float buffer[cols];
			for (int o=0;o<cols;o++){
				buffer[o] = matrix[i][o];
			}
			for (int o=0;o<cols;o++){
				matrix[i][o] -= (buffer[0]*matrix[0][o]);
			}
			draw_matrix(matrix, rows, cols);
		}	
	}
}

int main(){
	printf("RREF Solver\nHow many rows? ");
	int rows = 0, cols = 0;
	scanf("%d", &rows);
	printf("How many columns? ");
	scanf("%d", &cols);
	printf("Solving for %dx%d matrix...\n",rows,cols);
	float ** matrix_array = malloc(rows*sizeof(int*));
	for (int i=0;i<rows;i++){
		matrix_array[i] = malloc(cols*sizeof(int));
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
	return 0;
}
