#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector_tests.h"
#include "../../include/liblinal/liblinal.h"

static bool vector_tests_add_should_succeed() {
    bool result = true;

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

    float *s1 = v1.scalars;
    float *s2 = v2.scalars; 

    LA_Vector la_vector_add_result = {0};
    if(!la_vector_add(&v1, &v2, &la_vector_add_result)) {
        fprintf(stderr, "- Failed to find result of v1 + v2.\n");
        result = false;
    } else {
        float *result_scalars = la_vector_add_result.scalars;
        for(size_t cursor = 0; cursor < la_vector_add_result.dimension; cursor++) {
            if(result == false)
                break;
            float expected = *s1 + *s2;
            if(fabs(*(result_scalars + cursor) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Scalar addition values did not match.\n");
                result = false;
                break;
            }

            ++s1;
            ++s1;
        }
    }

    if(result)
        printf("+ Test for vector addition passed.\n");

    return result;
}

static bool vector_tests_subtract_should_succeed() {
    bool result = true;

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

    float *s1 = v1.scalars;
    float *s2 = v2.scalars; 

    LA_Vector la_vector_subtract_result = {0};
    if(!la_vector_add(&v1, &v2, &la_vector_subtract_result)) {
        fprintf(stderr, "- Failed to find result of v1 - v2.\n");
        result = false;
    } else {
        float *result_scalars = la_vector_subtract_result.scalars;
        for(size_t cursor = 0; cursor < la_vector_subtract_result.dimension; cursor++) {
            if(result == false)
                break;
            float expected = *s1 - *s2;
            if(fabs(*(result_scalars + cursor) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Scalar subtraction values did not match.\n");
                result = false;
                break;
            }

            ++s1;
            ++s1;
        }
    }

    if(result)
        printf("+ Test for vector subtraction passed.\n");

    return result;
}

static bool vector_tests_multiply_and_divide_should_succeed() {
    bool result = true;

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

    float *s1 = v1.scalars;
    float *s2 = v2.scalars;

    LA_Vector la_vector_multiply_result = {0};
    if(!la_vector_multiply(&v1, &v2, &la_vector_multiply_result)) {
        fprintf(stderr, "- Failed to find result of v1 * v2.\n");
        result = false;
    } else { 
        float *result_scalars = la_vector_multiply_result.scalars;
        for(size_t cursor = 0; cursor < la_vector_multiply_result.dimension; cursor++) {
            if(result == false)
                break;
            float expected = (*s1 * *s2);
            if(fabs((*result_scalars + cursor) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Scalar multiplication values did not match.\n");
                result = false;
                break;
            }

            ++s1;
            ++s2;
        }
    }

    s1 = v1.scalars;
    s2 = v2.scalars;

    LA_Vector la_vector_divide_result = {0};
    if(!la_vector_divide(&v1, &v2, &la_vector_divide_result)) {
        fprintf(stderr, "- Failed to find result of v1 / v2.\n");
        result = false;
    } else {
        float *result_scalars = la_vector_divide_result.scalars;
        for(size_t cursor = 0; cursor < la_vector_multiply_result.dimension; cursor++) {
            if(result == false)
                break;
            float expected = (*s1 / *s2);
            if(fabs(*(result_scalars + cursor) - expected) > (EPSILON * fabs(expected))) {
                fprintf(stderr, "- Scalar division values did not match.\n");
                result = false;
                break;
            }

            ++s1;
            ++s2;
        }
    }

    if(result)
        printf("+ Test for vector multiplication and division passed.\n");

    return result;
}

static bool vector_tests_is_equal_should_succeed() { 
    bool result = true;

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
    if(!la_vector_is_equal(&v1, &v2, &call_result)) {
        fprintf(stderr, "- Could not compare vectors, equality check failed.");
        result = false;
    }

    bool local_result = true;
    for(int cursor = 0; cursor < (int)v1.dimension; cursor++)
        if(fabsf(v2.scalars[cursor] - v1.scalars[cursor]) > EPSILON) {
            local_result = false;
            break;
        }
 
    return (result)
        ? (call_result == local_result)
        : result;
}

static bool vector_tests_get_cross_product_should_succeed() {
    bool result = true;

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
    if(!la_vector_cross(&v1, &v2, &v_result)) {
        fprintf(stderr, "- Could not calculate cross product of vectors, function returned false (failure).");
        result = false;
    } else {
        for(size_t cursor = 0; cursor < v1.dimension; cursor++)
            if(fabsf(v_result.scalars[cursor] - scalar_results[cursor]) > EPSILON) {
                fprintf(stderr, "- Cross product values did not match.\n");
                result = false;
                break;
            }
    }

    return result;
}

bool vector_tests_ops() {
    bool result = true;

    if(!vector_tests_is_equal_should_succeed()) {
        fprintf(stderr, "- Success path for vector equality tests returned false (failure).\n");
        result = false;
    }

    if(!vector_tests_get_cross_product_should_succeed()) {
        fprintf(stderr, "- Success path for vector cross product tests returned false (failure).\n");
        result = false;
    }
 
    return result;
}

bool vector_tests_arithmetic() {
    bool result = true;
    if(!vector_tests_add_should_succeed()) {
        fprintf(stderr, "- Success path for vector addition tests returned false (failure).\n");
        result = false;
    }

    if(!vector_tests_subtract_should_succeed()) {
        fprintf(stderr, "- Success path for vector subtraction tests returned false (failure).\n");
        result = false;
    }

    if(!vector_tests_multiply_and_divide_should_succeed()) {
        fprintf(stderr, "- Success path for vector multiplication and division returned false (failure).\n");
        result = false;
    }
 
    return result;
}

bool run_vector_tests() {
    bool result = true;

    if(!vector_tests_ops()) {
        fprintf(stderr, "- Vector operation tests returned false (failure).\n");
        result = false;
    }

    if(!vector_tests_arithmetic()) {
        fprintf(stderr, "- Vector arithmetic tests returned false (failure).\n");
        result = false;
    }
 
    return result;
}

