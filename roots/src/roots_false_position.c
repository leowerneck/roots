#include "roots.h"
#include "utils.h"

/*
 * Function   : roots_false_position
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using the false position method.
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
 * References : https://en.wikipedia.org/wiki/Regula_falsi
 */
roots_error_t
roots_false_position(
    double f(double const, void *restrict),
    void *restrict fparams,
    double a,
    double b,
    roots_params *restrict r ) {

  // Step 0: Set basic info to the roots_params struct
  sprintf(r->method, "False position");
  r->a = a;
  r->b = b;

  // Step 1: Check whether a or b is the root; compute fa and fb
  double fa, fb;
  if( check_a_b_compute_fa_fb(f, fparams, &a, &b, &fa, &fb, r) >= roots_success )
    return r->error_key;

  // Step 2: False-position algorithm
  for(r->n_iters=0;r->n_iters<r->iter_max;r->n_iters++) {
    // Step 2.a: Compute the new point
    const double c  = (a*fb - b*fa) / (fb-fa);
    const double fc = f(c, fparams);

    // Step 2.b: Check for convergence
    if( fabs(c-b) < r->tol || fc == 0.0 ) {
      r->root     = c;
      r->residual = fc;
      return (r->error_key = roots_success);
    }

    // Step 2.c: Adjust the interval, making sure the root is still in [a,b]
    if( fa*fc < 0 ) {
      b  = c;
      fb = fc;
    }
    else {
      a  = c;
      fa = fc;
    }
  }

  // Step 3: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed.
  return (r->error_key = roots_error_max_iter);
}
