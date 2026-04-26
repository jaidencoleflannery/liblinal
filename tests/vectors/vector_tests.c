#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "vector_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool vector_tests_add_and_subtract_should_succeed(float epsilon) {
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

    LA_Vector subtract_result = {0};
    if(!subtract(&v1, &v2, &subtract_result)) {
        fprintf(stderr, "- Failed to find result of v1 - v2.\n");
        return false;
    }  

    float *v1_scalar = v1.scalars;
    float *v2_scalar = v2.scalars;
    float *result_scalar = subtract_result.scalars;
    for(int cursor = 0; cursor < subtract_result.dimension; cursor++) {
        float expected = fabs(*v1_scalar - *v2_scalar);
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    LA_Vector add_result = {0};
    if(!add(&v1, &v2, &add_result)) {
        fprintf(stderr, "- Failed to find result of v1 + v2.\n");
        return false;
    }

    v1_scalar = v1.scalars;
    v2_scalar = v2.scalars;
    result_scalar = add_result.scalars;
    for(int cursor = 0; cursor < add_result.dimension; cursor++) {
        float expected = *v1_scalar + *v2_scalar;
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("+ Test for vector addition and subtraction passed.\n");
    return true;
}

bool vector_tests_add(float epsilon) {
    if(!vector_tests_add_and_subtract_should_succeed(epsilon)) {
        fprintf(stderr, "- vector_tests_add_should_succeed() returned false (failure).\n");
        return false;
    }
    
    return true;
}

