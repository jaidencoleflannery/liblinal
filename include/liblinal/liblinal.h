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

// vector ops.

bool la_vector_is_equal(LA_Vector *v1, LA_Vector *v2, bool *result);

bool la_vector_calculate_l2_norm(size_t dimension, float *scalars, float *l2_result);

bool la_vector_dot(LA_Vector *v1, LA_Vector *v2, float *result);

bool la_vector_cross(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

// vector arithmetic.

bool la_vector_add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_vector_subtract(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_vector_multiply(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

bool la_vector_scale(LA_Vector *v1, float scalar, LA_Vector *result);

bool la_vector_divide(LA_Vector *v1, LA_Vector *v2, LA_Vector *result);

// matrices.

typedef struct {
    size_t rows;
    size_t columns;
    // data is row contiguous, step num columns to reach next row.
    float *data;
} LA_Matrix;

// matrix ops.

bool la_matrix_is_equal(LA_Matrix *m1, LA_Matrix *m2, bool *result);

bool la_matrix_get(LA_Matrix *m, int row, int column, float *result);

bool la_matrix_set(LA_Matrix *m, int row, int column, float value);

bool la_matrix_get_row(LA_Matrix *m, int row, LA_Matrix *result);

bool la_matrix_get_column(LA_Matrix *m, int column, LA_Matrix *result);

// matrix arithmetic.

bool la_matrix_add(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result);

bool la_matrix_subtract(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result);

bool la_matrix_multiply(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result);

bool la_matrix_hadamard(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result);

// random.

typedef bool (*operation)(float, float, float *);

#endif
