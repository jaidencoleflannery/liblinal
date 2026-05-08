#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool matrix_tests_add_and_subtract_should_succeed() {
    bool result = true;

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

    float *d1 = m1.data;
    float *d2 = m2.data;

    LA_Matrix la_matrix_subtract_result = {0};
    if(!la_matrix_subtract(&m1, &m2, &la_matrix_subtract_result)) {
        fprintf(stderr, "- Failed to find result of m1 - m2.\n");
        result = false;
    } else { 
        float *result_data = la_matrix_subtract_result.data; 
        for(int row = 0; row < m1.rows; row++) {
            int offset = row * m1.columns;
            for(int column = 0; column < m1.columns; column++) {
                float expected = *(d1 + offset + column) - *(d2 + offset + column);
                if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                    fprintf(stderr, "- Matrix subtraction values did not match.\n");
                    result = false;
                }
            }
        }
    }

    LA_Matrix la_matrix_add_result = {0};
    if(!la_matrix_add(&m1, &m2, &la_matrix_add_result)) {
        fprintf(stderr, "- Failed to find result of m1 + m2.\n");
        result = false;
    } else {
        float *result_data = la_matrix_add_result.data;
        for(int row = 0; row < m1.rows; row++) {
            int offset = row * m1.columns;
            for(int column = 0; column < m1.columns; column++) {
                float expected = *(d1 + offset + column) + *(d1 + offset + column);
                if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                    fprintf(stderr, "- Matrix addition values did not match.\n");
                    result = false;
                }
            }
        }
    }

    if(result)
        printf("+ Test for matrix addition and subtraction passed.\n");

    return result;
}

static bool matrix_tests_multiply_and_hadamard_should_succeed() {
    bool result = true;

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

    float *d1 = m1.data;
    float *d2 = m2.data;

    LA_Matrix la_matrix_hadamard_result = {0};
    if(!la_matrix_hadamard(&m1, &m2, &la_matrix_hadamard_result)) {
        fprintf(stderr, "- Failed to find hadamard result of v1 * v2.\n");
        result = false;
    } else { 
        float *result_data = la_matrix_hadamard_result.data;

        for(int row = 0; row < m1.rows; row++) {
            int offset = row * m1.columns;
            for(int column = 0; column < m1.columns; column++) {
                float expected = *(d1 + offset + column) * *(d1 + offset + column);
                if(fabsf(*(result_data + offset + column) - expected) > (EPSILON * fabsf(expected))) {
                    fprintf(stderr, "- Matrix hadamard multiplication values did not match.\n");
                    result = false;;
                }
            }
        }
    }

    LA_Matrix la_matrix_multiply_result = {0};
    if(!la_matrix_multiply(&m1, &m2, &la_matrix_multiply_result)) {
        fprintf(stderr, "- Failed to find result of m1 * m2.\n");
        result = false;
    } else {
        float *result_data = la_matrix_multiply_result.data; 

        for(int row = 0; row < m1.rows; row++) {
            float expected = 0.0f;
            int offset = row * m1.columns;
            for(int cursor = 0; cursor < m1.columns; cursor++) {
                for(int column = 0; column < m1.columns; column++)
                    expected += d1[column + (row * m1.columns)] * d2[(column * m2.columns) + cursor];
                if(fabsf((result_data[(row * m1.columns) + cursor]) - expected) > (EPSILON * fabsf(expected))) {
                    fprintf(stderr, "- Matrix multiplication values did not match.\n");
                    return false;
                }
            }
        }
    } 
    

    if(result)
        printf("+ Test for matrix multiplication and hadamard multiplication passed.\n");

    return result;
}

static bool matrix_tests_is_equal_should_succeed() { 
    bool result = true;

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
        result = false;
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

    if(result) {
        printf("+ Test for matrix equality passed.\n");
        return (call_result == local_result);
    }
 
    return result;
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

    if(!matrix_tests_multiply_and_hadamard_should_succeed()) {
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

