#ifndef UTILS_H_
#define UTILS_H_

/*
 * Function   : swap
 * Author     : Leo Werneck
 *
 * Swaps the values of two doubles a and b.
 *
 * Parameters : a        - First number.
 *            : b        - Second number.
 *
 * Returns    : Nothing.
 */
static inline void
swap(
    double *restrict a,
    double *restrict b ) {

  const double c = *a;
  *a = *b;
  *b = c;
}

/*
 * Function   : ensure_b_is_closest_to_root
 * Author     : Leo Werneck
 *
 * Given a, b, f(a), f(b), ensures |f(b)| < |f(a)|.
 *
 * Parameters : a        - First point where f(x) is evaluated at.
 *            : b        - Second point where f(x) is evaluated at.
 * Parameters : fa       - f(a)
 *            : fb       - f(b).
 *
 * Returns    : Nothing.
 */
static inline void
ensure_b_is_closest_to_root(
    double *restrict a,
    double *restrict b,
    double *restrict fa,
    double *restrict fb ) {

  if( fabs(*fa) < fabs(*fb) ) {
    swap(a, b);
    swap(fa, fb);
  }
}

/***********************
 * Function prototypes *
 ***********************/
// This function is implemented in check_a_b_compute_fa_fb.c
roots_error_t
check_a_b_compute_fa_fb(
    double f(const double, void *restrict),
    void   *restrict params,
    double *restrict a,
    double *restrict b,
    double *restrict fa,
    double *restrict fb,
    roots_params *restrict r );

#endif // UTILS_H_
