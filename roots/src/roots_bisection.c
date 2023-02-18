#include "roots.h"
#include "utils.h"

roots_error_t
check_a_b_compute_fa_fb(
    double f(void *restrict, const double),
    void   *restrict params,
    double *restrict a,
    double *restrict b,
    double *restrict fa,
    double *restrict fb,
    roots_params *restrict r );

/*
 * Function   : roots_bisection
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using the bisection method.
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
 * References : https://en.wikipedia.org/wiki/Bisection_method
 */
roots_error_t
roots_bisection(
    double f(void *restrict, double const),
    void *restrict params,
    double a,
    double b,
    roots_params *restrict r ) {

  sprintf(r->method, "bisection");
  r->a = a;
  r->b = b;

  // Step 1: Check whether a or b is the root; compute fa and fb
  double fa, fb;
  if( check_a_b_compute_fa_fb(f, params, &a, &b, &fa, &fb, r) >= roots_success )
    return r->error_key;

  // Step 2: Bisection algorithm
  for(r->n_iters=0;r->n_iters<r->iter_max;r->n_iters++) {
    // Step 2.a: Compute the mid point and the function at the midpoint
    const double c  = (a+b)/2;
    const double fc = f(params, c);

    // Step 2.b: Adjust the limits of the interval
    if( fa*fc < 0 ) {
      b  = c;
      fb = fc;
    }
    else {
      a  = c;
      fa = fc;
    }

    // Step 2.c: Keep best root in b
    ensure_b_is_closest_to_root(&a, &b, &fa, &fb);

    // Step 2.d: Check for convergence
    if( fabs(fb) < r->ftol || fabs(b-a) < r->xtol ) {
      r->root     = b;
      r->residual = fb;
      return (r->error_key = roots_success);
    }
  }

  // Step 3: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed.
  return (r->error_key = roots_error_max_iter);
}
