#ifndef LIBLINAL_H
#define LIBLINAL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// vectors.

typedef struct {
    size_t dimension;
    float l2_norm;
    float *scalars;
} LA_Vector;

bool calculate_l2_norm(int dimension, float *scalars, float *l2_result);

bool is_equal(LA_Vector *v1, LA_Vector *v2, bool *result);

// vector arithmetic-esque operations.

bool add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool subtract(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool multiply(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool scale(LA_Vector *v1, float scalar, LA_Vector *result);

bool divide(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

// matrices.

typedef struct {
    int rows;
    int columns;
} LA_Matrix_Size;

typedef struct {
    LA_Matrix_Size size; 
    float *data; // the 2d array can just be one long contiguous block, you can count which column you're in by the num of rows from .size.
} LA_Matrix;

#endif
