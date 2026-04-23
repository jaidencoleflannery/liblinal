#ifndef LIBLINAL_H
#define LIBLINAL_H

#include "../../include/liblinal/liblinal.h"

#define la_get_vector(scalars) _Generic((scalars), \
        short *: la_get_vector_short, \
        int *: la_get_vector_int, \
        double *: la_get_vector_int, \

LA_Vector *la_get_vector(int *scalars);

LA_Vector *la_get_vector(double *scalars);

double la_get_scalar(int component);

#endif
