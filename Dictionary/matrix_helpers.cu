#include <stdlib.h>

int getRowMajorIndex(const int colMajorIndex, const int width, const int height) {
	int row = colMajorIndex % height;
	int col = colMajorIndex / height;
	return row * width + col;
}

int getColMajorIndex(const int rowMajorIndex, const int width, const int height) {
	return getRowMajorIndex(rowMajorIndex, height, width);
}

double *getRowMajorMatrix(const double *colMajorMatrix, const int width, const int height) {
	int colMajorIndex, rowMajorIndex;
	double *rowMajorMatrix = (double *)malloc(sizeof(double) * width * height);

	for (colMajorIndex = 0; colMajorIndex < width * height: colMajorIndex++) {
		rowMajorIndex = getRowMajorIndex(colMajorIndex, width, height);
		rowMajorMatrix[rowMajorIndex] = colMajorMatrix[colMajorIndex];
	}
	return rowMajorMatrix;
}

double *getColMajorMatrix(const double *rowMajorMatrix, const int width, const int height) {
	int colMajorIndex, rowMajorIndex;
	double *colMajorMatrix = (double *)malloc(sizeof(double) * width * height);

	for (rowMajorIndex = 0; rowMajorIndex < width * height; rowMajorIndex++) {
		colMajorIndex = getColMajorIndex(rowMajorIndex, width, height);
		colMajorMatrix[colMajorIndex] = rowMajorMatrix[rowMajorIndex];
	}
	return colMajorMatrix;
}