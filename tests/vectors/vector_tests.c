#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "vector_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool vector_tests_la_add_and_la_subtract_should_succeed(float epsilon) {
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

    LA_Vector la_subtract_result = {0};
    if(!la_subtract(&v1, &v2, &la_subtract_result)) {
        fprintf(stderr, "- Failed to find result of v1 - v2.\n");
        return false;
    }  

    float *v1_scalar = v1.scalars;
    float *v2_scalar = v2.scalars;
    float *result_scalar = la_subtract_result.scalars;
    for(int cursor = 0; cursor < (int)la_subtract_result.dimension; cursor++) {
        float expected = (*v1_scalar - *v2_scalar);
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar la_subtraction values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    LA_Vector la_add_result = {0};
    if(!la_add(&v1, &v2, &la_add_result)) {
        fprintf(stderr, "- Failed to find result of v1 + v2.\n");
        return false;
    }

    v1_scalar = v1.scalars;
    v2_scalar = v2.scalars;
    result_scalar = la_add_result.scalars;
    for(int cursor = 0; cursor < (int)la_add_result.dimension; cursor++) {
        float expected = *v1_scalar + *v2_scalar;
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar la_addition values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("+ Test for vector la_addition and la_subtraction passed.\n");
    return true;
}

static bool vector_tests_la_multiply_and_la_divide_should_succeed(float epsilon) {
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

    LA_Vector la_multiply_result = {0};
    if(!la_multiply(&v1, &v2, &la_multiply_result)) {
        fprintf(stderr, "- Failed to find result of v1 * v2.\n");
        return false;
    }

    float *v1_scalar = v1.scalars;
    float *v2_scalar = v2.scalars;
    float *result_scalar = la_multiply_result.scalars;
    for(int cursor = 0; cursor < (int)la_multiply_result.dimension; cursor++) {
        float expected = (*v1_scalar * *v2_scalar);
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar multiplication values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    LA_Vector la_divide_result = {0};
    if(!la_divide(&v1, &v2, &la_divide_result)) {
        fprintf(stderr, "- Failed to find result of v1 / v2.\n");
        return false;
    }

    v1_scalar = v1.scalars;
    v2_scalar = v2.scalars;
    result_scalar = la_divide_result.scalars;
    for(int cursor = 0; cursor < (int)la_multiply_result.dimension; cursor++) {
        float expected = (*v1_scalar / *v2_scalar);
        if(fabs(*result_scalar - expected) > (epsilon * fabs(expected))) {
            fprintf(stderr, "- Scalar division values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("+ Test for vector multiplication and division passed.\n");
    return true;
}

bool vector_tests_arithmetic(float epsilon) {
    if(!vector_tests_la_add_and_la_subtract_should_succeed(epsilon)) {
        fprintf(stderr, "- vector_tests_la_add_and_la_subtract_should_succeed() returned false (failure).\n");
        return false;
    }

    if(!vector_tests_la_multiply_and_la_divide_should_succeed(epsilon)) {
        fprintf(stderr, "- vector_tests_la_multiply_and_la_divide_should_succeed() returned false (failure).\n");
        return false;
    }
 
    return true;
}

static bool vector_tests_is_equal_should_succeed(float epsilon) {
    return true;
}

static bool vector_tests_get_cross_product_should_succeed(float epsilon) {
    return true;
}

bool vector_tests_ops(float epsilon) {
    if(!vector_tests_is_equal_should_succeed(epsilon)) {
        fprintf(stderr, "- vector_tests_is_equal_should_succeed() returned false (failure).\n");
        return false;
    }

    if(!vector_tests_get_cross_product_should_succeed(epsilon)) {
        fprintf(stderr, "- vector_tests_get_cross_product_should_succeed() returned false (failure).\n");
        return false;
    }
 
    return true;
}

