// Row <-> col major interconverters
int getRowMajorIndex(const int colMajorIndex, const int width, const int height);
int getColMajorIndex(const int rowMajorIndex, const int width, const int height);

double *getRowMajorMatrix(const double *colMajorMatrix, const int width, const int height);
double *getColMajorMatrix(const double *rowMajorMatrix, const int width, const int height);