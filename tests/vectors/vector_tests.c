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
        fprintf(stderr, "main.c: Failed to find l2 norm for v1 vector.");
        return -1;
    }

    LA_Vector v2 = {
        .dimension = 3,
        .l2_norm = 0.0f,
        .scalars = &scalars[0]
    };

    if(!calculate_l2_norm(v2.dimension, v2.scalars, &v2.l2_norm)) {
        fprintf(stderr, "main.c: Failed to find l2 norm for v2 vector.");
        return -1;
    }

    LA_Vector result = {0};
    if(!add(&v1, &v2, &result)) {
        fprintf(stderr, "main.c: Failed to find result of v1 + v2.");
        return -1;
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

    return true;
}

bool vector_tests_add(float epsilon) {
    if(!vector_tests_add_should_succeed(epsilon)) {
        fprintf(stderr, "vector_tests_add_should_succeed() returned false (failure).");
        return false;
    }
    
    return true;
}

