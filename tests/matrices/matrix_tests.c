#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool matrix_tests_add_and_subtract_should_succeed() {

    static float *m1_scalars[3][3] = { 
        { 0.1f, 1.8994f, 16.42f },
        { 99.4f, 1.8994f, 18.42f },
        { 0.002f, 14.1f, 1.0f },
    };

    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .scalars = &m1_scalars[0][0];
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

bool matrix_tests_ops() {
    if(!matrix_tests_is_equal_should_succeed()) {
        fprintf(stderr, "- Success path for matrix equality tests returned false (failure).\n");
        return false;
    }
 
    return true;
}

bool matrix_tests_arithmetic() {
    if(!matrix_tests__add_and_subtract_should_succeed()) {
        fprintf(stderr, "- Success path for matrix addition and subtraction tests returned false (failure).\n");
        return false;
    }

    if(!matrix_tests_multiply_and_divide_should_succeed()) {
        fprintf(stderr, "- Success path for matrix multiplication and division tests returned false (failure).\n");
        return false;
    }
 
    return true;
}

bool run_matrix_tests() {
    if(!matrix_tests_ops()) {
        fprintf(stderr, "- Matrix operation tests returned false (failure).\n");
        return false;
    }

    if(!matrix_tests_arithmetic()) {
        fprintf(stderr, "- Matrix arithmetic tests returned false (failure).\n");
        return false;
    }
 
    return true;
}

