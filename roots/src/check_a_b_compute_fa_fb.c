#include "roots.h"
#include "utils.h"

/*
 * Function   : check_a_b_compute_fa_fb
 * Author     : Leo Werneck
 *
 * This function is used at the beginning of the root-finding methods. It
 * performs the following tasks:
 *
 *   1. Check if either a or b are roots of f;
 *   2. Check if the root is in the interval [a,b];
 *   3. Ensure |f(b)| < |f(a)| by swapping a and b if necessary.
 *
 * Parameters : f        - Function for which the root is computed.
 *            : fparams  - Object containing all parameters needed by the
 *                         function f other than the variable x.
 *            : a        - Lower limit of the initial interval.
 *            : b        - Upper limit of the initial interval.
 *            : fa       - f(a)
 *            : fb       - f(b)
 *            : r        - Pointer to roots library parameters (see roots.h).
 *
 * Returns    : One the following error keys:
 *                 - roots_success if the root is found
 *                 - roots_continue if the root is not found but no errors
 *                   occurred
 *                 - roots_error_root_not_bracketed if the interval [a,b]
 *                   does not bracket a root of f(x)
 */
roots_error_t
check_a_b_compute_fa_fb(
    double f(double const, void *restrict),
    void   *restrict fparams,
    double *restrict a,
    double *restrict b,
    double *restrict fa,
    double *restrict fb,
    roots_params *restrict r ) {

  // Step 1: Compute fa; check if a is the root.
  *fa = f(*a, fparams);
  if( fabs(*fa) < r->ftol ) {
    r->root     = *a;
    r->residual = *fa;
    return (r->error_key = roots_success);
  }

  // Step 2: Compute fb; check if b is the root.
  *fb = f(*b, fparams);
  if( fabs(*fb) < r->ftol ) {
    r->root     = *b;
    r->residual = *fb;
    return (r->error_key = roots_success);
  }

  // Step 3: Ensure the root is in [a,b]
  if( (*fa)*(*fb) > 0 )
    return (r->error_key = roots_error_root_not_bracketed);

  // Step 4: Ensure b contains the best approximation to the root
  ensure_b_is_closest_to_root(a, b, fa, fb);

  // Step 5: If [a,b] is too small, return b
  if( fabs(*a - *b) < r->xtol ) {
    r->root     = *b;
    r->residual = *fb;
    return (r->error_key = roots_success);
  }

  // Step 6: Root not found.
  return roots_continue;
}
