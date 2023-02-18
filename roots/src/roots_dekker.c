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
roots_error_t
roots_dekker(
    double f(void *restrict, double const),
    void *restrict params,
    double a,
    double b,
    roots_params *restrict r ) {

  sprintf(r->method, "dekker");
  r->a = a;
  r->b = b;

  // Step 1: Check whether a or b is the root; compute fa and fb
  double fa, fb;
  if( check_a_b_compute_fa_fb(f, params, &a, &b, &fa, &fb, r) >= roots_success )
    return r->error_key;

  // Step 2: Define d, such that f(d) * f(b) < 0 (initially a).
  double d = a;

  // Step 3: Dekker's algorithm
  for(r->n_iters=0;r->n_iters<r->iter_max;r->n_iters++) {
    // Step 3.a: Compute the midpoint
    const double m = (b+d)/2;

    // Step 3.b: Compute the secant method
    const double s = fa != fb ? b - fb * (b-a) / (fb-fa) : m;

    // Step 3.c: Set the next guess for the root
    const double c = (s>b && s<m) ? s : m;

    // Step 3.d: Compute the next function value
    const double fc = f(params, c);

    // Step 3.e: Cicle the values of a, b, fa, fb
    if( fa*fb < 0 ) {
      b  = c;
      fb = fc;
    }
    else {
      d  = b;
      a  = c;
      fa = fc;
    }

    // Step 3.f: Keep best root in b
    ensure_b_is_closest_to_root(&a, &b, &fa, &fb);

    // Step 3.h: Check for convergence
    if( fabs(fb) < r->ftol || fabs(b-a) < r->xtol ) {
      r->root     = b;
      r->residual = fb;
      return (r->error_key = roots_success);
    }
  }

  // Step 4: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed.
  return (r->error_key = roots_error_max_iter);
}
