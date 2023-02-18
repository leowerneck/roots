#ifndef ROOTS_H_
#define ROOTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
  roots_continue=-1,
  roots_success,
  roots_error_root_not_bracketed,
  roots_error_max_iter
} roots_error_t;

typedef struct roots_params {
  roots_error_t error_key;
  char method[1024];
  unsigned int n_iters, iter_max;
  double a, b;
  double residual, root, xtol, ftol;
} roots_params;

void
roots_info(const roots_params *restrict r);

roots_error_t
roots_bisection(
    double f(double const, void *restrict),
    void *restrict params,
    double a,
    double b,
    roots_params *restrict r );

roots_error_t
roots_secant(
    double f(double const, void *restrict),
    void *restrict params,
    double a,
    double b,
    roots_params *restrict r );

roots_error_t
roots_dekker(
    double f(double const, void *restrict),
    void *restrict params,
    double a,
    double b,
    roots_params *restrict r );

#endif // ROOTS_H_
