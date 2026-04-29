#include "../../include/liblinal/liblinal.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define EPSILON 1e-6f
#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'

static bool find_largest_scalar_absolute(int dimension, float *scalars, float *largest_scalar) {
    if(dimension <= 0) {
        fprintf(stderr, "The parameter dimension must be a positive integer.\n");
        return false;
    }

    if(scalars == NULL) {
        fprintf(stderr, "Provided scalars pointer was NULL.\n");
        return false;
    }

    if(largest_scalar == NULL) {
        fprintf(stderr, "Provided largest_scalar pointer was NULL.\n");
        return false;
    } 

    *largest_scalar = 0.0f;
    for(int cursor = 0; cursor < dimension; cursor++)
        if(fabs(*(scalars + cursor)) > *largest_scalar)
            *largest_scalar = fabs(*(scalars + cursor));

    if(*largest_scalar < 0.0f) {
        fprintf(stderr, "Failed to find largest scalar, result was less than 0.\n");
        return false;
    }

    return true;
}

bool la_calculate_l2_norm(size_t dimension, float *scalars, float *l2_result) {
    if(dimension <= 0) {
        fprintf(stderr, "The parameter dimension must be a positive integer.\n");
        return false;
    }

    if(scalars == NULL) {
        fprintf(stderr, "Provided scalars pointer was NULL.\n");
        return false;
    }

    if(l2_result == NULL) {
        fprintf(stderr, "Provided l2_result pointer was NULL.\n");
        return false;
    }
    
    // we divide all values by the largest scalar to _hopefully_ avoid overflow,
    // at the end we scale the result back up by the same value so our result is the "same".
    float largest_scalar;
    if(!find_largest_scalar_absolute(dimension, scalars, &largest_scalar)) {
        fprintf(stderr, "Failed to find largest scalar.\n");
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
        return true; // save some compute for the other guy.

    // find the square root of the sum via heron's method.
    float seeker = fabs(*l2_result / 2.0f);
    while(fabs((seeker * seeker) - *l2_result) > EPSILON * seeker) {
        float result = (*l2_result / seeker);
        seeker = ((seeker + result) / 2);
    }
    
    *l2_result = (seeker * largest_scalar); // scale back up.

    return true;
}

static bool arithmetic_op(LA_Vector *v1, LA_Vector *v2, char type, LA_Vector *result) {
    if(type != '+' && type != '-' && type != '*' && type != '/') {
        fprintf(stderr, "Invalid type value.\n");
        return false;
    }

    if(v1 == NULL || v2 == NULL) {
        fprintf(stderr, "One of the provided vector pointers was NULL.\n");
        return false;
    }

    if(v1->dimension != v2->dimension) {
        fprintf(stderr, "Dimensions were of different sizes.\n");
        return false;
    }

    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    result->dimension = (int)v1->dimension; 

    float *v1_cursor = v1->scalars;
    float *v2_cursor = v2->scalars;

    result->scalars = (float *)malloc(result->dimension * sizeof(float));
    if(result->scalars == NULL) {
        free(result->scalars);
        fprintf(stderr, "Failed to allocate memory.\n");
        return false;
    }

    for(int cursor = 0; cursor < (int)v1->dimension; cursor++) {
        switch(type) {
            case '+': 
                result->scalars[cursor] = (v1_cursor[cursor] + v2_cursor[cursor]);
                break;

            case '-':
                result->scalars[cursor] = (v1_cursor[cursor] - v2_cursor[cursor]);
                break;

            case '*':
                result->scalars[cursor] = (v1_cursor[cursor] * v2_cursor[cursor]);
                break;

            case '/':
                result->scalars[cursor] = (v1_cursor[cursor] / v2_cursor[cursor]);
                break;
        } 
    }

    float l2_norm;
    la_calculate_l2_norm(result->dimension, result->scalars, &l2_norm);
    result->l2_norm = l2_norm;

    return true;
}

bool la_add(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    if(!arithmetic_op(v1, v2, ADD, result)) {
        fprintf(stderr, "Failed to add vectors.\n");
        return false;
    }

    return true;
}

bool la_subtract(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    if(!arithmetic_op(v1, v2, SUBTRACT, result)) {
        fprintf(stderr, "Failed to subtract vectors.\n");
        return false;
    }

    return true;
}

bool la_multiply(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    if(!arithmetic_op(v1, v2, MULTIPLY, result)) {
        fprintf(stderr, "Failed to multiply vectors.\n");
        return false;
    }

    return true;
}

bool la_scale(LA_Vector *v1, float scalar, LA_Vector *result) {
    float *v1_cursor = v1->scalars;
    for(int cursor = 0; cursor < (int)v1->dimension; cursor++)
        result->scalars[cursor] = (*v1_cursor++ * scalar);

    return true;
}

bool la_cross(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    int required_dimension = 3;

    if(v1 == NULL || v1->scalars == NULL) {
        fprintf(stderr, "The provided vector pointer {v1} was invalid.\n");
        return false;
    }

    if(v2 == NULL || v2->scalars == NULL) {
        fprintf(stderr, "The provided vector pointer {v2} was invalid.\n");
        return false;
    }

    if(result == NULL) {
        fprintf(stderr, "The provided vector pointer {result} was invalid.\n");
        return false;
    }

    if(v1->dimension != required_dimension || v2->dimension != required_dimension) {
        fprintf(stderr, "Vectors for cross product calculation must be 3 dimensional.\n");
        return false;
    }

    if(v1 == result || v2 == result) {
        fprintf(stderr, "Vectors for cross product calculation must be unique (instance was provided more than once).\n");
        return false;
    }

    result->dimension = required_dimension;

    float *scalar_cache = malloc(v1->dimension * sizeof(float));
    if(scalar_cache == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return false;
    } 

    if(result->scalars != NULL) {
        free(result->scalars);
    }

    result->scalars = scalar_cache;

    float *s1 = v1->scalars;
    float *s2 = v2->scalars;
    float *r = result->scalars;
    r[0] = (s1[1] * s2[2]) - (s1[2] * s2[1]);
    r[1] = (s1[2] * s2[0]) - (s1[0] * s2[2]);
    r[2] = (s1[0] * s2[1]) - (s1[1] * s2[0]);

    float l2_norm;
    la_calculate_l2_norm(result->dimension, result->scalars, &l2_norm);
    result->l2_norm = l2_norm;

    return true;
}

bool la_divide(LA_Vector *v1, LA_Vector *v2, LA_Vector *result) {
    if(!arithmetic_op(v1, v2, DIVIDE, result)) {
        fprintf(stderr, "Failed to divide vectors.\n");
        return false;
    }

    return true;
}

bool la_dot(LA_Vector *v1, LA_Vector *v2, float *result) {
    if(v1 == NULL || v2 == NULL) {
        fprintf(stderr, "One of the provided vector pointers was NULL.\n");
        return false;
    }

    if(v1->dimension != v2->dimension) {
        fprintf(stderr, "Dimensions were of different sizes.\n");
        return false;
    }

    if(result == NULL) {
        fprintf(stderr, "Provided result pointer was NULL.\n");
        return false;
    }

    *result = 0.0f;

    float *v1_cursor = v1->scalars;
    float *v2_cursor = v2->scalars;
    for(int cursor = 0; cursor < (int)v1->dimension; cursor++)
        *result += (v1_cursor[cursor] * v2_cursor[cursor]);

    return true;
}

bool la_is_equal(LA_Vector *v1, LA_Vector *v2, bool *result) {
    if(v1 == NULL || v2 == NULL) {
        fprintf(stderr, "One of the provided vector pointers was NULL.\n");
        *result = false;
        return false; // failure.
    }

    if(v1->dimension != v2->dimension) {
        *result = false;
        return true; // still successful.
    }

    float *v1_cursor = v1->scalars;
    float *v2_cursor = v2->scalars;

    for(int cursor = 0; cursor < (int)v1->dimension; cursor++) {
        // floats only store ~6 trustworthy values, if the value grows too large we lose accuracy;
        // epsilon has to be relative to size of diff to cover that :(
        float diff = (fabsf(v1_cursor[cursor] - v2_cursor[cursor]));
        if(diff > (EPSILON * diff)) {
            *result = false;
            return true;
        }
    }

    *result = true;
    return true;
}

