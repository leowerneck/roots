#include "roots.h"
#include "utils.h"

/*
 * Function   : roots_dekker
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using Dekker's method.
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
 * References : https://en.wikipedia.org/wiki/Brent%27s_method
 */
double
roots_dekker(
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

  // Step 3: Check the root is in [a,b].
  if( f0*f1 > 0 )
    roots_error(roots_error_root_not_bracketed,
                "Interval (%g,%g) does not bracket the root\n", a, b);

  // Step 4: Keep the better guess in x1.
  if( fabs(f1) > fabs(f0) ) {
    swap(&x0, &x1);
    swap(&f0, &f1);
  }

  // Step 5: Define op, such that f(op) * f(x1) < 0 (initially x0).
  double op = x0;

  // Step 6: Perform Dekker's method algorithm
  for(int it=0;it<r->itmax;it++) {
    // Step 6.a: Compute the midpoint
    const double xm = (x1+op)/2;

    // Step 6.b: Compute the secant method
    const double xs = f1 != f0 ? x1 - f1 * (x1-x0) / (f1-f0) : xm;

    // Step 6.c: Set the next guess for the root
    const double x2 = (xs>x1 && xs<xm) ? xs : xm;

    // Step 6.d: Compute the next function value
    const double f2 = f(params, x2);

    // Step 6.e: Cicle the values of x0, x1, f0, f1
    if( f0*f2 < 0 ) {
      x1 = x2;
      f1 = f2;
    }
    else {
      op = x1;
      x0 = x2;
      f0 = f2;
    }

    // Step 6.f: Keep the better guess in x1.
    if( fabs(f1) > fabs(f0) ) {
      swap(&x0, &x1);
      swap(&f0, &f1);
    }

    // Step 6.h: Check for convergence
    if( fabs(f1) < r->ftol || fabs(x1-x0) < r->xtol )
      return x2;
  }

  // Step 5: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed; error out.
  roots_error(roots_error_max_iter,
              "Exceeded maximum number of iterations (%d)\n", r->itmax);
  return roots_error_max_iter;
}
