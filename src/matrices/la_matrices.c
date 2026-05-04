#include "../../include/liblinal/liblinal.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef bool (*operation)(float, float, float *);

static bool add(float a, float b, float *result) {
    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    *result = a + b;
    return true;
}

static bool subtract(float a, float b, float *result) {
    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    *result = a - b;
    return true;
}

static bool multiply(float a, float b, float *result) {
    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    *result = a * b;
    return true;
}

static bool divide(float a, float b, float *result) {
    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    *result = a / b;
    return true;
}

static bool arithmetic_op(LA_Matrix *m1, LA_Matrix *m2, operation op, LA_Matrix *result) {
    if(m1 == NULL || m2 == NULL) {
        fprintf(stderr, "One of the provided matrix pointers were NULL.\n");
        return false;
    }

    if(m1->rows != m2->rows || m1->columns != m2->columns) {
        fprintf(stderr, "Provided matrices have differing dimensions, could not add.");
        return false;
    }

    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    for(size_t column = 0; column < m1->columns; column++) {
        size_t offset = (column * m1->rows);
        for(size_t row = 0; row < m1->rows; row++) {
             if(!op(m1->data[offset], m2->data[offset], &(result->data[offset]))) {
                 fprintf(stderr, "Failed to perform operation on matrices.");
                return false;
             }
        }
    }

    return true;
}

bool la_matrix_add(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result) {
    if(!arithmetic_op(m1, m2, &add, result)) {
        fprintf(stderr, "Failed to perform addition on matrices.");
        return false;
    }

    return true;
}

bool la_matrix_subtract(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result) {
    if(!arithmetic_op(m1, m2, &subtract, result)) {
        fprintf(stderr, "Failed to perform subtraction on matrices.");
        return false;
    }

    return true;
}

bool la_matrix_multiply(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result) {
    if(!arithmetic_op(m1, m2, &multiply, result)) {
        fprintf(stderr, "Failed to perform multiplication on matrices.");
        return false;
    }

    return true;
}

bool la_matrix_divide(LA_Matrix *m1, LA_Matrix *m2, LA_Matrix *result) {
    if(!arithmetic_op(m1, m2, &divide, result)) {
        fprintf(stderr, "Failed to perform multiplication on matrices.");
        return false;
    }

    return true;
}

bool la_matrix_is_equal(LA_Matrix *m1, LA_Matrix *m2, bool *result) {
    if(m1 == NULL || m2 == NULL || result == NULL) {
        fprintf(stderr, "A provided pointer was NULL.");
        return false;
    }

    if(m1->rows != m2->rows || m1->columns != m2->columns) {
        *result = false;
        return true;
    } 

    // matrix data is contiguous, just check every float.
    size_t matrix_size = m1->columns * m1->rows;
    for(size_t cursor  = 0; cursor < matrix_size; cursor++) {
        float s1 = m1->data[cursor];
        float s2 = m2->data[cursor];
        // if value is 0 or extremely small, relative epsilon doesn't work.
        if(fabsf(s1) < EPSILON || fabsf(s2) < EPSILON) {
            if(fabsf(s1 - s2) > EPSILON) {
                *result = false;
                return true;
            }
        } else if(fabsf(s1 - s2) > fabsf(EPSILON * s1)) {
            *result = false;
            return true;
        }
    }
    
    *result = true;
    return true;
}

bool la_matrix_get(LA_Matrix *m, int row, int column, float *result) {
    if(m == NULL || result == NULL) {
        fprintf(stderr, "A provided pointer was NULL");
        return false;
    }

    if(row > m->rows || column > m->columns) {
        fprintf(stderr, "Index queried is out of bounds for the provided matrix.");
        return false;
    }

    *result = m->data[(row * m->columns) + column];
    return true;
}

bool la_matrix_set(LA_Matrix *m, int row, int column, float value) {
    if(m == NULL) {
        fprintf(stderr, "The provided matrix pointer was NULL");
        return false;
    }

    if(row > m->rows || column > m->columns) {
        fprintf(stderr, "Index queried is out of bounds for the provided matrix.");
        return false;
    }

    m->data[(row * m->columns) + column] = value;
    if(m->data[(row * m->columns) + column] == value)
        return true;
    else
        fprintf(stderr, "Failed to insert value.");
    return false;
}

