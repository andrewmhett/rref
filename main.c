#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void draw_matrix(int ** matrix, int rows, int cols){
	int col_widths[cols];
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			col_widths[o]=0;
			char str_value[10];
			sprintf(str_value, "%d", matrix[i][o]);
			if (strlen(str_value)>col_widths[o]){
				col_widths[o]=(int)strlen(str_value);
			}
		}
	}	
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			char str_value[10];
			sprintf(str_value, "%d", matrix[i][o]);
			printf("%d",matrix[i][o]);
			for (int n=-1;n<col_widths[o]-(int)strlen(str_value);n++){
				printf(" ");
			}
		}
		printf("\n");
	}
}

void rref_matrix(int ** original_matrix, int row, int cols){
	
}

int main(){
	printf("RREF Solver\nHow many rows? ");
	int rows = 0, cols = 0;
	scanf("%d", &rows);
	printf("How many columns? ");
	scanf("%d", &cols);
	printf("Solving for %dx%d matrix...\n",rows,cols);
	int ** matrix_array = malloc(rows*sizeof(int*));
	for (int i=0;i<rows;i++){
		matrix_array[i] = malloc(cols*sizeof(int));
	}
	for (int i=0;i<rows;i++){
		for (int o=0;o<cols;o++){
			printf("Row %d, Column %d: ",i+1,o+1);
			scanf("%d", &matrix_array[i][o]);
		}
	}
	printf("INITIAL MATRIX\n");
	draw_matrix(matrix_array, rows, cols);
	rref_matrix(matrix_array, rows, cols);
	return 0;
}
