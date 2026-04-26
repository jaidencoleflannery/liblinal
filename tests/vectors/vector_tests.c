#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "vector_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool vector_tests_add_should_succeed(float epsilon) {
    float scalars[] = { 0.1f, 1.8f, 16.4f };

    LA_Vector v1 = {
        .dimension = 3,
        .l2_norm = 0.0f,
        .scalars = &scalars[0]
    };

    if(!calculate_l2_norm(v1.dimension, v1.scalars, &v1.l2_norm)) {
        fprintf(stderr, "Failed to find l2 norm for v1 vector.");
        return false;
    }

    LA_Vector v2 = {
        .dimension = 3,
        .l2_norm = 0.0f,
        .scalars = &scalars[0]
    };

    if(!calculate_l2_norm(v2.dimension, v2.scalars, &v2.l2_norm)) {
        fprintf(stderr, "Failed to find l2 norm for v2 vector.");
        return false;
    }

    LA_Vector result = {0};
    if(!add(&v1, &v2, &result)) {
        fprintf(stderr, "Failed to find result of v1 + v2.");
        return false;
    } 

    float *v1_scalar = v1.scalars;
    float *v2_scalar = v2.scalars;
    for(int cursor = 0; cursor < result.dimension; cursor++) {
        float diff = fabs(*v1_scalar - *v2_scalar);
        if(diff > (epsilon * diff))
            return false;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("\n* Test for vector addition passed.\n");
    return true;
}

static bool vector_tests_subtract_should_succeed(float epsilon) {
    float v1_scalars[] = { 0.1f, 1.8994f, 16.42f };

    LA_Vector v1 = {
        .dimension = 3,
        .l2_norm = 0.0f,
        .scalars = &v1_scalars[0]
    };

    float v2_scalars[] = { 4.13f, 1.8f, 16.4705f };

    LA_Vector v2 = {
        .dimension = 3,
        .l2_norm = 0.0f,
        .scalars = &v2_scalars[0]
    };

    LA_Vector result = {0};
    if(!subtract(&v1, &v2, &result)) {
        fprintf(stderr, "Failed to find result of v1 - v2.");
        return false;
    } 

    float *v1_scalar = v1.scalars;
    float *v2_scalar = v2.scalars;
    float *result_scalar = result.scalars;
    for(int cursor = 0; cursor < result.dimension; cursor++) {
        float expected = fabs(*v1_scalar - *v2_scalar);
        if((fabs(*result_scalar) - expected) > (epsilon * expected))
            return false;

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("\n* Test for vector subtraction passed.\n");
    return true;
}

bool vector_tests_add(float epsilon) {
    if(!vector_tests_add_should_succeed(epsilon)) {
        fprintf(stderr, "vector_tests_add_should_succeed() returned false (failure).");
        return false;
    }

    if(!vector_tests_subtract_should_succeed(epsilon)) {
        fprintf(stderr, "vector_tests_subtract_should_succeed() returned false (failure).");
        return false;
    }
    
    return true;
}

