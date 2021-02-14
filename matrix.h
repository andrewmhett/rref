void swap_rows(float ** matrix, int row_1, int row_2){
	float * buffer = matrix[row_1];
	matrix[row_1] = matrix[row_2];
	matrix[row_2] = buffer;
}

void normalize_row(float ** matrix, int row, int cols){
	float buffer[cols];
	for (int i=0;i<cols;i++){
		buffer[i] = matrix[row][i];
	}
	for (int i=0;i<cols;i++){
		matrix[row][i]/=buffer[row];
	}
}
