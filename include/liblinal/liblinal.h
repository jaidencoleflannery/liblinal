#ifndef LIBLINAL_H
#define LIBLINAL_H

#include <stdint.h>
#include <stdbool.h>

// vectors

typedef struct {
    int dimension;
    float l2_norm;
    float *scalars;
} LA_Vector;

bool calculate_l2_norm(int dimension, float *scalars, float *l2_result);

bool add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool subtract(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

// multiply()

// divide()

bool is_equal(LA_Vector *v1, LA_Vector *v2, bool *result);

// matrices

typedef struct {
    int rows;
    int columns;
} LA_Matrix_Size;

typedef struct {
    LA_Matrix_Size size; 
    float *data; // the 2d array can just be one long contiguous block, you can count which column you're in by the num of rows from .size.
} LA_Matrix;

#endif
