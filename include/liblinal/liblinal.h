#ifndef LIBLINAL_H
#define LIBLINAL_H

typedef struct LA_Matrix_Size LA_Matrix_Size;

typedef struct {
    int dimension;
    double l2_norm;
    double *scalars; 
} LA_Vector;

typedef struct {
    LA_Matrix_Size *size;
    double *data; // note: the 2d array can just be one long contiguous block, you can count which column you're in by the number of rows from {size}.
} LA_Matrix;

#endif
