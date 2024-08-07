#ifndef ROOTS_H_
#define ROOTS_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  roots_continue = -1,
  roots_success,
  roots_error_root_not_bracketed,
  roots_error_max_iter
} roots_error_t;

typedef struct roots_params {
  roots_error_t error_key;
  char method[1024];
  unsigned int n_iters, max_iters;
  double a, b;
  double residual, root, tol;
} roots_params;

void roots_info(const roots_params *restrict r);

roots_error_t roots_bisection(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_secant(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_false_position(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_dekker(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_ridder(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_brent(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

roots_error_t roots_toms748(
      double f(const double, void *restrict),
      void *restrict params,
      double a,
      double b,
      roots_params *restrict r);

#endif  // ROOTS_H_
