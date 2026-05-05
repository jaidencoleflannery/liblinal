#ifndef LIBLINAL_H
#define LIBLINAL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define EPSILON 1e-6f

// vectors.

typedef struct {
    size_t dimension;
    float l2_norm;
    float *scalars;
} LA_Vector;

// vector ops

bool la_is_equal(LA_Vector *v1, LA_Vector *v2, bool *result);

bool la_cross(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_calculate_l2_norm(size_t dimension, float *scalars, float *l2_result);

// vector arithmetic-esque operations.

bool la_add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_subtract(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_multiply(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_scale(LA_Vector *v1, float scalar, LA_Vector *result);

bool la_divide(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

// matrices.

typedef struct {
    size_t rows;
    size_t columns;
    // the 2d array is one contiguous block of memory.
    // data is stored in sections of .rows length, to jump from [0, 0] to [0, 1] you'd skip .rows elements.
    float *data;
} LA_Matrix;

// rand.

typedef bool (*operation)(float, float, float *);

#endif
