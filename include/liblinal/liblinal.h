#ifndef LIBLINAL_H
#define LIBLINAL_H

#include <stdint.h>

typedef struct LA_Matrix_Size LA_Matrix_Size;

typedef struct {
    int dimension;
    float l2_norm;
    float *scalars;
} LA_Vector;

typedef struct {
    LA_Matrix_Size *size;
    // note: the 2d array can just be one long contiguous block, you can count which column you're in by the number of rows from {size}.
    float *data; 
} LA_Matrix;

#endif
