#include "../../include/liblinal/la_vectors.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define EPSILON 1e-6f

static bool find_largest_scalar(float *scalars, int dimension, float *largest_scalar) {
    if(scalars == NULL) {
        fprintf(stderr, "Provided scalars pointer was NULL.");
        return false;
    }

    if(largest_scalar == NULL) {
        fprintf(stderr, "Provided largest_scalar pointer was NULL.");
        return false;
    }

    if(dimension <= 0) {
        fprintf(stderr, "Parameter dimension must be a positive integer.");
        return false;
    }

    *largest_scalar = 0.0f;
    for(int cursor = 0; cursor < dimension; cursor++)
        if(fabs(*(scalars + cursor)) > *largest_scalar)
            *largest_scalar = fabs(*(scalars + cursor));

    if(*largest_scalar < 0.0f) {
        fprintf(stderr, "Failed to find largest scalar, result was less than 0.");
        return false;
    }

    return true;
}

bool calculate_l2_norm(int dimension, float *scalars, float *l2_result) {
    if(dimension <= 0) {
        fprintf(stderr, "Dimension must be non-negative.");
        return false;
    }

    if(l2_result == NULL) {
        fprintf(stderr, "Provided l2_result pointer was NULL.");
        return false;
    } 

    if(scalars == NULL) {
        fprintf(stderr, "Provided scalars pointer was NULL.");
        return false;
    }

    float largest_scalar;
    if(!find_largest_scalar(scalars, dimension, &largest_scalar)) {
        fprintf(stderr, "Failed to find largest scalar.");
        return false;
    }

    *l2_result = 0.0f;
    float *scalar_cursor = scalars;

    // square and add.
    for(int cursor = 0; cursor < dimension; cursor++) {
        *l2_result += (*scalar_cursor / largest_scalar) * (*scalar_cursor / largest_scalar);
        ++scalar_cursor;
    }

    if(*l2_result == 0.0f)
        return true;

    // find the square root of the sum.
    float seeker = fabs(*l2_result / 2.0f);
    while(fabs((seeker * seeker) - *l2_result) > EPSILON * seeker) {
        float result = (*l2_result / seeker);
        seeker = ((seeker + result) / 2);
    }

    *l2_result = (seeker * largest_scalar);

    return true;
}

bool add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    if(v1->dimension != v2->dimension)
        return false;

    result->dimension = v1->dimension; 

    float *v1_cursor = v1->scalars;
    float *v2_cursor = v2->scalars;

    result->scalars = (float *)malloc(v1->dimension * sizeof(float));
    if(result->scalars == NULL) {
        free(result->scalars);
        fprintf(stderr, "Failed to allocate memory.");
        return false;
    }

    for(int cursor = 0; cursor < v1->dimension; cursor++)
        result->scalars[cursor] = (v1_cursor[cursor] + v2_cursor[cursor]); 

    double l2_norm;
    calculate_l2_norm(result->dimension, result->scalars, &l2_norm);
    result->l2_norm = l2_norm;

    return true;
}

bool is_equal(LA_Vector *v1, LA_Vector *v2) {
    if(v1->dimension != v2->dimension)
        return false;

    float *v1_cursor = v1->scalars;
    float *v2_cursor = v2->scalars;

    for(int cursor = 0; cursor < v1->dimension; cursor++)
        if(fabsf(v1_cursor[cursor] - v2_cursor[cursor]) > EPSILON)
            return false;

    return true;
}

