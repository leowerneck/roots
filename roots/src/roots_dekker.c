#include "roots.h"
#include "utils.h"

/*
 * Function   : roots_dekker
 * Author     : Leo Werneck
 *
 * Find the root of f(x) in the interval [a,b] using Dekker's method.
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
 * References : https://en.wikipedia.org/wiki/Brent%27s_method
 */
roots_error_t
roots_dekker(
    double f(double const, void *restrict),
    void *restrict fparams,
    double a,
    double b,
    roots_params *restrict r ) {

  // Step 0: Set basic info to the roots_params struct
  sprintf(r->method, "Dekker's");
  r->a = a;
  r->b = b;

  // Step 1: Check whether a or b is the root; compute fa and fb
  double fa, fb;
  if( check_a_b_compute_fa_fb(f, fparams, &a, &b, &fa, &fb, r) >= roots_success )
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
    const double fc = f(c, fparams);

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
    if( fabs(b-a) < r->tol || fb == 0.0 ) {
      r->root     = b;
      r->residual = fb;
      return (r->error_key = roots_success);
    }
  }

  // Step 4: The only way to get here is if we have exceeded the maximum number
  //         of iterations allowed.
  return (r->error_key = roots_error_max_iter);
}
