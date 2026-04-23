#ifndef LIBLINAL_H
#define LIBLINAL_H

#include <stdint.h>

typedef struct {
    uint64_t component[4];
} LA_Component;

typedef struct {
    int dimension;
    double l2_norm;
    LA_Component *scalars; 
} LA_Vector;

typedef struct LA_Matrix_Size LA_Matrix_Size;

typedef struct {
    LA_Matrix_Size *size;
    // note: the 2d array can just be one long contiguous block, you can count which column you're in by the number of rows from {size}.
    LA_Component *data; 
} LA_Matrix;

#endif
