#include "roots.h"
#include "utils.h"

/*
 * Function   : roots_ridder
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using Ridder's method.
 *
 * Parameters : f        - Function for which the root is computed.
 *            : fparams  - Object containing all parameters needed by the
 *                         function f other than the variable x.
 *            : a        - Lower limit of the initial interval.
 *            : b        - Upper limit of the initial interval.
 *            : r        - Pointer to roots library parameters (see roots.h).
 *                         The root is stored in r->root.
 *
 * Returns    : One the following error keys:
 *                 - roots_success if the root is found
 *                 - roots_error_root_not_bracketed if the interval [a,b]
 *                   does not bracket a root of f(x)
 *                 - roots_error_max_iter if the maximum allowed number of
 *                   iterations is exceeded
 *
 * References : https://en.wikipedia.org/wiki/Ridders%27_method
 */
roots_error_t
roots_ridder(
    double f(double const, void *restrict),
    void *restrict fparams,
    double a,
    double b,
    roots_params *restrict r ) {

  // Step 0: Set basic info to the roots_params struct
  sprintf(r->method, "Ridder's");
  r->a = a;
  r->b = b;

  // Step 1: Check whether a or b is the root; compute fa and fb
  double fa, fb;
  if( check_a_b_compute_fa_fb(f, fparams, &a, &b, &fa, &fb, r) >= roots_success )
    return r->error_key;

  // Step 2: False-position algorithm
  for(r->n_iters=1;r->n_iters<=r->iter_max;r->n_iters++) {

    // Step 2.a: Compute the midpoint
    const double m  = (a+b)/2;
    const double fm = f(m, fparams);

    // Step 2.b: Check for convergence
    if( fabs(m-a) < r->tol || fm == 0.0 ) {
      r->root     = m;
      r->residual = fm;
      return (r->error_key = roots_success);
    }

    // Step 2.c: Compute new point
    const double d  = sqrt(fm*fm - fa*fb);
    const double c  = m + (m-a)*sign(fa-fb)*fm/d;
    const double fc = f(c, fparams);

    // Step 2.d: Check for convergence
    if( fabs(c-b) < r->tol || fc == 0.0 ) {
      r->root     = c;
      r->residual = fc;
      return (r->error_key = roots_success);
    }

    // Step 2.e: Adjust the interval
    if( fm*fc < 0 ) {
      a  = m;
      b  = c;
      fa = fm;
      fb = fc;
    }
    else if( fa*fc < 0 ) {
      a  = c;
      fa = fc;
    }
    else {
      b  = c;
      fb = fc;
    }

    // Step 2.f: Ensure the best guess for the root is in b
    ensure_b_is_closest_to_root(&a, &b, &fa, &fb);
  }

  // Step 3: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed.
  return (r->error_key = roots_error_max_iter);
}
