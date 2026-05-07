#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool matrix_tests_add_and_subtract_should_succeed() {

    static float m1_scalars[3][3] = { 
        { 0.1f, 1.8994f, 16.42f },
        { 99.4f, 1.8994f, 18.42f },
        { 0.002f, 14.1f, 1.0f },
    };

    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = m1_scalars[0]
    };

    static float m2_scalars[3][3] = { 
        { 44.1f, 1.89f, 3.2f },
        { 9.4f, 299.4f, 1.42f },
        { 7.2f, 14.1f, 1.4f },
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = m2_scalars[0]
    };

    LA_Matrix la_matrix_subtract_result = {0};
    if(!la_matrix_subtract(&m1, &m2, &la_matrix_subtract_result)) {
        fprintf(stderr, "- Failed to find result of m1 - m2.\n");
        return false;
    }  

    float *m1_data = m1.data;
    float *m2_data = m2.data;
    float *result_data = la_matrix_subtract_result.data;
    int columns = m1.columns;
    for(int row = 0; row < m1.rows; row++) {
        int offset = row * columns;
        for(int column = 0; column < m1.columns; column++) {
            float expected = *(m1_data + offset + column) - *(m2_data + offset + column);
            if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Matrix subtraction values did not match.\n");
                return false;
            }
        }
    }

    LA_Matrix la_matrix_add_result = {0};
    if(!la_matrix_add(&m1, &m2, &la_matrix_add_result)) {
        fprintf(stderr, "- Failed to find result of m1 + m2.\n");
        return false;
    }

    result_data = la_matrix_add_result.data;
    for(int row = 0; row < m1.rows; row++) {
        int offset = row * columns;
        for(int column = 0; column < m1.columns; column++) {
            float expected = *(m1_data + offset + column) + *(m2_data + offset + column);
            if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Matrix addition values did not match.\n");
                return false;
            }
        }
    }

    printf("+ Test for matrix addition and subtraction passed.\n");
    return true;
}

static bool matrix_tests_is_equal_should_succeed() { 
    static float m1_scalars[3][3] = { 
        { 0.1f, 1.8994f, 16.42f },
        { 99.4f, 1.8994f, 18.42f },
        { 0.002f, 14.1f, 1.0f },
    };

    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = m1_scalars[0]
    };

    static float m2_scalars[3][3] = { 
        { 44.1f, 1.89f, 3.2f },
        { 9.4f, 299.4f, 1.42f },
        { 7.2f, 14.1f, 1.4f },
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = m2_scalars[0]
    };

    bool call_result;
    if(!la_matrix_is_equal(&m1, &m2, &call_result)) {
        fprintf(stderr, "- Could not compare matrices, equality check failed.");
        return false;
    }

    bool local_result = true;
    const int columns = m1.columns;

    for(int row = 0; row < m1.rows; row++) { 
        int offset = row * columns;
        for(int column = 0; column < m1.columns; column++) {
            if(fabsf(*(m1.data + offset + column)) - fabsf(*(m2.data + offset + column)) > EPSILON) {
                fprintf(stderr, "- Matrix values did not match.\n");
                local_result = false;
            }
        }
    }
 
    return (call_result == local_result);
}

bool matrix_tests_ops() {
    if(!matrix_tests_is_equal_should_succeed()) {
        fprintf(stderr, "- Success path for matrix equality tests returned false (failure).\n");
        return false;
    }
 
    return true;
}

bool matrix_tests_arithmetic() {
    if(!matrix_tests_add_and_subtract_should_succeed()) {
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

