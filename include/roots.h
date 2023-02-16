#ifndef ROOTS_H_
#define ROOTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
  roots_error_abort=-1,
  roots_success,
  roots_error_root_not_bracketed,
  roots_error_max_iter,
} roots_error_t;

typedef struct roots_params {
  unsigned int itmax;
  double xtol, ftol;
} roots_params;

void
roots_info(const char *format, ...);

void
roots_Warn_Error(
      const char *type,
      const int exit_code,
      const char *filename,
      const int line,
      const char *funcname,
      const char *format,
      ...);

#define roots_warn(format, ...) \
  roots_Warn_Error("Warning", roots_success, __FILE__, __LINE__, __func__, format __VA_OPT__(,) __VA_ARGS__)

#define roots_error(exit_code, format, ...) \
  roots_Warn_Error("Error", exit_code, __FILE__, __LINE__, __func__, format __VA_OPT__(,) __VA_ARGS__)

#define roots_abort(format, ...) \
  roots_Warn_Error("Error", roots_error_abort, __FILE__, __LINE__, __func__, format __VA_OPT__(,) __VA_ARGS__)

double
roots_bisection(
    double f(void *restrict, double const),
    void *restrict params,
    const double a,
    const double b,
    const roots_params *restrict r );

double
roots_secant(
    double f(void *restrict, double const),
    void *restrict params,
    const double a,
    const double b,
    const roots_params *restrict r );

#endif // ROOTS_H_
