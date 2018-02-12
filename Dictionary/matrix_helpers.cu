int getRowMajorIndex(const int colMajorIndex, const int width, const int height) {
	int row = colMajorIndex % height;
	int col = colMajorIndex / height;
	return row * width + col;
}

int getColMajorIndex(const int rowMajorIndex, const int width, const int height) {
	return getRowMajorIndex(rowMajorIndex, height, width);
}