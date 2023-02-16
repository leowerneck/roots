#include "roots.h"

/*
 * Function   : roots_secant
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using the secant method.
 *
 * Parameters : f        - Function for which the root is computed.
 *            : params   - Object containing all parameters needed by the
 *                         function f other than the variable x.
 *            : a        - Lower limit of the initial interval.
 *            : b        - Upper limit of the initial interval.
 *            : r        - Steering parameters (see roots.h).
 *
 * Returns    : The root of f(x).
 *
 * References : https://en.wikipedia.org/wiki/Secant_method
 */
double
roots_secant(
    double f(void *restrict, double const),
    void *restrict params,
    const double a,
    const double b,
    const roots_params *restrict r ) {

  // Step 1: Check if a is the root.
  double x0 = a;
  double f0 = f(params, x0);
  if( fabs(f0) < r->ftol )
    return x0;

  // Step 2: Check if b is the root.
  double x1 = b;
  double f1 = f(params, x1);
  if( fabs(f1) < r->ftol )
    return x1;

  // Step 3: Check the root is in [a,b]
  if( f0*f1 > 0 )
    roots_error(roots_error_root_not_bracketed,
                "Interval (%g,%g) does not bracket the root\n", a, b);

  // Step 4: Perform the secant algorithm
  for(int it=0;it<r->itmax;it++) {
    // Step 4.a: Compute the new point
    const double x2 = x1 - f1 * (x1-x0) / (f1-f0);
    const double f2 = f(params, x2);

    // Step 4.b: Check for convergence
    if( fabs(f2) < r->ftol || fabs(x2-x1) < r->xtol )
      return x2;

    // Step 4.c: Cicle the value of x0, x1, f0, f1
    x0 = x1;
    f0 = f1;
    x1 = x2;
    f1 = f2;
  }

  // Step 5: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed; error out.
  roots_error(roots_error_max_iter,
              "Exceeded maximum number of iterations (%d)\n", r->itmax);
  return roots_error_max_iter;
}