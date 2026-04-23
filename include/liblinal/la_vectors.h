#ifndef LIBLINAL_VECTORS_H
#define LIBLINAL_VECTORS_H

#include "liblinal.h"

LA_Vector la_get_vector(int dimension, float *scalars);

float la_get_scalar(LA_Vector *vector, int component);

#endif
