#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool vector_tests_add_and_subtract_should_succeed() {
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
        if(fabs(*result_scalar - expected) > (EPSILON * fabs(expected))) {
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
        if(fabs(*result_scalar - expected) > (EPSILON * fabs(expected))) {
            fprintf(stderr, "- Scalar addition values did not match.\n");
            return false;
        }

        ++result_scalar;
        ++v1_scalar;
        ++v2_scalar;
    }

    printf("+ Test for vector addition and subtraction passed.\n");
    return true;
}

static bool vector_tests_multiply_and_divide_should_succeed() {
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
        if(fabs(*result_scalar - expected) > (EPSILON * fabs(expected))) {
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
        if(fabs(*result_scalar - expected) > (EPSILON * fabs(expected))) {
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

static bool vector_tests_is_equal_should_succeed() { 
    LA_Vector v1 = {
        .dimension = 3,
        .l2_norm = 0.0,
        .scalars = (float[]){ 2.4, 1.0, 8.9 }
    };
    LA_Vector v2 = {
        .dimension = 3,
        .l2_norm = 0.0,
        .scalars = (float[]){ 0.8, 9.1, 4.9 }
    }; 

    bool call_result;
    if(!la_is_equal(&v1, &v2, &call_result)) {
        fprintf(stderr, "- Could not compare vectors, equality check failed.");
        return false;
    }

    bool local_result = true;
    for(int cursor = 0; cursor < (int)v1.dimension; cursor++)
        if(fabsf(v2.scalars[cursor] - v1.scalars[cursor]) > EPSILON)
            local_result = false;
 
    return (call_result == local_result);
}

static bool vector_tests_get_cross_product_should_succeed() {
    LA_Vector v1 = {
        .dimension = 3,
        .l2_norm = 0.0,
        .scalars = (float[]){ 2.4, 1.0, 8.9 }
    };
    LA_Vector v2 = {
        .dimension = 3,
        .l2_norm = 0.0,
        .scalars = (float[]){ 0.8, 9.1, 4.9 }
    };

    float scalar_results[] = (float[]){ -76.09, -4.64, 21.04 };
    LA_Vector v_result = {0};
    if(!la_cross(&v1, &v2, &v_result)) {
        fprintf(stderr, "- Could not calculate cross product of vectors, function returned false (failure).");
        return false;
    }

    for(int cursor = 0; cursor < (int)v1.dimension; cursor++)
        if(fabsf(v_result.scalars[cursor] - scalar_results[cursor]) > EPSILON)
            return false;

    return true;
}

bool vector_tests_ops() {
    if(!vector_tests_is_equal_should_succeed()) {
        fprintf(stderr, "- Success path for vector equality tests returned false (failure).\n");
        return false;
    }

    if(!vector_tests_get_cross_product_should_succeed()) {
        fprintf(stderr, "- Success path for vector cross product tests returned false (failure).\n");
        return false;
    }
 
    return true;
}

bool vector_tests_arithmetic() {
    if(!vector_tests_add_and_subtract_should_succeed()) {
        fprintf(stderr, "- Success path for vector addition and subtraction tests returned false (failure).\n");
        return false;
    }

    if(!vector_tests_multiply_and_divide_should_succeed()) {
        fprintf(stderr, "- Success path for vector multiplication and division returned false (failure).\n");
        return false;
    }
 
    return true;
}

bool run_vector_tests() {
    if(!vector_tests_ops()) {
        fprintf(stderr, "- Vector operation tests returned false (failure).\n");
        return false;
    }

    if(!vector_tests_arithmetic()) {
        fprintf(stderr, "- Vector arithmetic tests returned false (failure).\n");
        return false;
    }
 
    return true; 
}

