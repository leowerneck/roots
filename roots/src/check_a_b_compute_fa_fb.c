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
    roots_params *restrict r ) {

  // Step 1: Compute fa; check if a is the root.
  *fa = f(params, *a);
  if( fabs(*fa) < r->ftol ) {
    r->root     = *a;
    r->residual = *fa;
    return (r->error_key = roots_success);
  }

  // Step 2: Compute fb; check if b is the root.
  *fb = f(params, *b);
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
