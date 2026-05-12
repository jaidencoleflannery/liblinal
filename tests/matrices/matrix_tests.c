#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool matrix_tests_add_should_succeed() { 
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){
            0.1f, 1.8994f, 16.42f,
            99.4f, 1.8994f, 18.42f,
            0.002f, 14.1f, 1.0f
        }
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){
            44.1f, 1.89f, 3.2f,
            9.4f, 299.4f, 1.42f,
            7.2f, 14.1f, 1.4f,
        }
    };

    float *d1 = m1.data;
    float *d2 = m2.data; 

    LA_Matrix la_matrix_add_result = {0};
    la_matrix_add_result.data = malloc(sizeof(float) * 9);
    if(la_matrix_add_result.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for matrix addition data.");
        return false;
    }

    if(!la_matrix_add(&m1, &m2, &la_matrix_add_result)) {
        fprintf(stderr, "- Failed to find result of m1 + m2.\n");
        free(la_matrix_add_result.data);
        return false;
    } 

    float *result_data = la_matrix_add_result.data;
    for(size_t row = 0; row < m1.rows; row++) {
        size_t offset = row * m1.columns;
        for(size_t column = 0; column < m1.columns; column++) {
            float expected = *(d1 + offset + column) + *(d2 + offset + column);
            if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Matrix addition values did not match.\n");
                free(la_matrix_add_result.data);
                return false;
            }
        }
    }

    printf("+ Test for matrix addition passed.\n");
    free(la_matrix_add_result.data);
    return true;
}

static bool matrix_tests_subtract_should_succeed() {
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f, 1.8994f, 16.42f,
            99.4f, 1.8994f, 18.42f,
            0.002f, 14.1f, 1.0f,
        }
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            44.1f, 1.89f, 3.2f,
            9.4f, 299.4f, 1.42f,
            7.2f, 14.1f, 1.4f,
        }
    };

    float *d1 = m1.data;
    float *d2 = m2.data;

    LA_Matrix la_matrix_subtract_result = {0};
    la_matrix_subtract_result.data = malloc(sizeof(float) * 9);
    if(la_matrix_subtract_result.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for matrix subtraction data.");
        return false;
    }

    if(!la_matrix_subtract(&m1, &m2, &la_matrix_subtract_result)) {
        fprintf(stderr, "- Failed to find result of m1 - m2.\n");
        free(la_matrix_subtract_result.data);
        return false;
    }

    float *result_data = la_matrix_subtract_result.data; 
    for(size_t row = 0; row < m1.rows; row++) {
        size_t offset = row * m1.columns;
        for(size_t column = 0; column < m1.columns; column++) {
            float expected = *(d1 + offset + column) - *(d2 + offset + column);
            if(fabs(*(result_data + offset + column) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Matrix subtraction values did not match.\n");
                free(la_matrix_subtract_result.data);
                return false;
            }
        }
    }
    
    printf("+ Test for matrix subtraction passed.\n");
    free(la_matrix_subtract_result.data);
    return true;
}

static bool matrix_tests_multiply_should_succeed() {
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f, 1.8994f, 16.42f,
            99.4f, 1.8994f, 18.42f,
            0.002f, 14.1f, 1.0f,
        }
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            44.1f, 1.89f, 3.2f,
            9.4f, 299.4f, 1.42f,
            7.2f, 14.1f, 1.4f,
        }
    }; 

    float *d1 = m1.data;
    float *d2 = m2.data;

    LA_Matrix la_matrix_multiply_result = {0};
    la_matrix_multiply_result.data = malloc(sizeof(float) * 9);
    if(la_matrix_multiply_result.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for matrix multiplication data.");
        return false;
    }

    if(!la_matrix_multiply(&m1, &m2, &la_matrix_multiply_result)) {
        fprintf(stderr, "- Failed to find result of m1 * m2.\n");
        free(la_matrix_multiply_result.data);
        return false;
    }

    float *result_data = la_matrix_multiply_result.data; 
    for(size_t row = 0; row < m1.rows; row++) {
        float expected = 0.0f;
        for(size_t cursor = 0; cursor < m1.columns; cursor++) {
            for(size_t column = 0; column < m1.columns; column++)
                expected += d1[column + (row * m1.columns)] * d2[(column * m2.columns) + cursor];
            if(fabsf((result_data[(row * m1.columns) + cursor]) - expected) > (EPSILON * fabsf(expected))) {
                fprintf(stderr, "- Matrix multiplication values did not match.\n");
                free(la_matrix_multiply_result.data);
                return false;
            }
        }
    }

    printf("+ Test for matrix multiplication passed.\n");
    free(la_matrix_multiply_result.data);
    return true;
}

static bool matrix_tests_hadamard_should_succeed() {
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f, 1.8994f, 16.42f,
            99.4f, 1.8994f, 18.42f,
            0.002f, 14.1f, 1.0f,
        }
    };

    LA_Matrix m2 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            44.1f, 1.89f, 3.2f,
            9.4f, 299.4f, 1.42f,
            7.2f, 14.1f, 1.4f,
        }
    }; 

    float *d1 = m1.data;
    float *d2 = m2.data;

    LA_Matrix la_matrix_multiply_result = {0};
    la_matrix_multiply_result.data = malloc(sizeof(float) * m1.rows * m2.columns);
    if(la_matrix_multiply_result.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for matrix hadamard multiplcation data.");
        return false;
    }

    if(!la_matrix_hadamard(&m1, &m2, &la_matrix_multiply_result)) {
        fprintf(stderr, "- Failed to find result of hadamard m1 * m2.\n");
        free(la_matrix_multiply_result.data);
        return false;
    }

    float *result_data = la_matrix_multiply_result.data; 
    for(size_t row = 0; row < m1.rows; row++) {
        size_t offset = row * m1.columns;
        for(size_t column = 0; column < m1.columns; column++) {
            float expected = *(d1 + offset + column) * *(d2 + offset + column);
            if(fabsf(*(result_data + offset + column) - expected) > (EPSILON * fabsf(expected))) {
                fprintf(stderr, "- Matrix hadamard multiplication values did not match.\n");
                free(la_matrix_multiply_result.data);
                return false;
            }
        }
    }

    printf("+ Test for matrix hadamard multiplication passed.\n");
    free(la_matrix_multiply_result.data);
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

    bool local_result;
    const size_t columns = m1.columns;

    for(size_t row = 0; row < m1.rows; row++) { 
        size_t offset = row * columns;
        for(size_t column = 0; column < m1.columns; column++) {
            if(fabsf(*(m1.data + offset + column)) - fabsf(*(m2.data + offset + column)) > EPSILON) {
                local_result = false;
                break;
            }
        }
    }

    const bool result = (call_result == local_result);

    if(result)
        printf("+ Test for matrix equality passed.\n");
    return result;
}

static bool matrix_tests_set_should_succeed() {  
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f,   1.894f, 16.42f,
            99.4f,  1.894f, 18.42f,
            0.002f, 14.1f,  1.000f
        }
    }; 

    LA_Matrix expected_matrix = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f,   9.999f, 16.42f,
            99.4f,  1.894f, 18.42f,
            0.002f, 14.1f,  1.000f
        }
    };

    if(!la_matrix_set(&m1, 0, 1, 9.999)) {
        fprintf(stderr, "- Could not set matrix value, set check failed.");
        return false;
    }

    bool result = true;
    for(size_t row = 0; row < m1.rows; row++) { 
        size_t offset = row * m1.columns;
        for(size_t column = 0; column < m1.columns; column++) {
            if(fabsf(*(m1.data + offset + column)) - fabsf(*(expected_matrix.data + offset + column)) > EPSILON) {
                result = false;
                break;
            }
        }
    }

    if(result)
        printf("+ Test for matrix set value passed.\n");
    else
        printf("+ Test for matrix set value failed.\n");
    return result;
}

static bool matrix_tests_get_row_should_succeed() {
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f,   1.894f, 16.42f,
            99.4f,  1.894f, 18.42f,
            0.002f, 14.1f,  1.000f
        }
    }; 

    // expected_row is hardcoded to the second row of m1.
    LA_Matrix expected_matrix = {
        .rows = 1,
        .columns = m1.columns,
        .data = m1.data + m1.columns
    };

    LA_Matrix *testing_matrix = malloc(sizeof(expected_matrix));
    testing_matrix->data = malloc(sizeof(float) * 3);

    if(!la_matrix_get_row(&m1, 1, testing_matrix)) {
        fprintf(stderr, "- Could not get matrix row, get check failed.");
        return false;
    }

    if(testing_matrix->rows > 1) {
        fprintf(stderr, "- Result of get had an invalid number of rows, get check failed.");
        return false;
    } 

    bool result = true;
    for(size_t column = 0; column < m1.columns; column++)
        if(fabsf(*(testing_matrix->data + column)) - fabsf(*(expected_matrix.data + column)) > EPSILON) {
            fprintf(stderr, "%f - %f\n", fabsf(*(testing_matrix->data + column)), fabsf(*(expected_matrix.data + column)));
            result = false;
            break;
        }

    free(testing_matrix->data);
    free(testing_matrix);
    (result)
        ? fprintf(stderr, "+ Test for matrix get row passed.\n")
        : fprintf(stderr, "- Test for matrix get row failed.\n");
    return result;
}

static bool matrix_tests_get_column_should_succeed() {  
    LA_Matrix m1 = {
        .rows = 3,
        .columns = 3,
        .data = (float[]){ 
            0.1f,   1.894f, 16.42f,
            99.4f,  1.894f, 18.42f,
            0.002f, 14.1f,  1.000f
        }
    }; 

    // expected_row is hardcoded to the second column of m1.
    LA_Matrix expected_matrix = {
        .rows = 1,
        .columns = 1,
        .data = (float[]){ 
            1.894f, 
            1.894f, 
            14.1f 
        }
    };

    LA_Matrix *testing_matrix = malloc(sizeof(LA_Matrix));
    testing_matrix->data = malloc(sizeof(float) * 3);

    if(!la_matrix_get_column(&m1, 1, testing_matrix)) {
        fprintf(stderr, "- Could not get matrix column, get check failed.");
        return false;
    }

    if(testing_matrix->columns > 1) {
        fprintf(stderr, "- Result of get column had an invalid number of columns, get check failed.");
        return false;
    }

    bool result = true;
    for(size_t row = 0; row < expected_matrix.rows; row++)
        if(fabsf(*(testing_matrix->data + row)) - fabsf(*(expected_matrix.data + row)) > EPSILON) {
            result = false;
            break;
        }

    free(testing_matrix->data);
    free(testing_matrix);
    (result)
        ? fprintf(stderr, "+ Test for matrix get column passed.\n")
        : fprintf(stderr, "- Test for matrix get column failed.\n");
    return result;
}

bool matrix_tests_ops() {
    bool result = true;

    if(!matrix_tests_is_equal_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix equality tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_set_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix set tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_get_row_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix get row tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_get_column_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix get column tests returned false (failure).\n");
        result = false;
    }
 
    return result;
}

bool matrix_tests_arithmetic() {
    bool result = true;

    if(!matrix_tests_add_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix addition tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_subtract_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix addition tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_multiply_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix multiplication tests returned false (failure).\n");
        result = false;
    }

    if(!matrix_tests_hadamard_should_succeed()) {
        fprintf(stderr, "-- Success path for matrix hadamard multiplication tests returned false (failure).\n");
        result = false;
    }
 
    return result;
}

bool run_matrix_tests() {
    bool result = true;

    if(!matrix_tests_ops())
        result = false;

    if(!matrix_tests_arithmetic())
        result = false;
 
    return result;
}

