#include "../../include/liblinal/la_vectors.h"

static float get_l2_norm(int dimension, float *scalars) {
    double l2_result = 0.0;
    float *scalar_cursor = scalars;
    while(*scalar_cursor++)
        l2_result += *scalar_cursor * *scalar_cursor;
}

LA_Vector la_get_vector(int dimension, float *scalars) {
    LA_Vector vector = { .dimension = dimension, .scalars = scalars, .l2_norm = get_l2_norm(dimension, scalars) };
    return vector;
}

