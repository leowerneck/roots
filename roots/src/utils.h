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
 * Function   : cicle
 * Author     : Leo Werneck
 *
 * From inputs a, b, c, set a, b, c = b, c, b.
 *
 * Parameters : a        - First number.
 *            : b        - Second number.
 *            : c        - Third number.
 *
 * Returns    : Nothing.
 */
static inline void
cicle(
    double *restrict a,
    double *restrict b,
    double *restrict c ) {

  *a = *b;
  *b = *c;
  *c = *b;
}

/*
 * Function   : sign
 * Author     : Leo Werneck
 *
 * Returns the sign of a number x.
 *
 * Parameters : x        - Number
 *            : b        - Second number.
 *
 * Returns    : +1 if x>=0, -1 otherwise.
 */
static inline int
sign( const double x ) {

  return (x>0) - (x<0);
}

/*
 * Function   : ensure_b_is_closest_to_root
 * Author     : Leo Werneck
 *
 * Given a, b, f(a), f(b), ensures |f(b)| < |f(a)|.
 *
 * Parameters : a        - First point where f(x) is evaluated at.
 *            : b        - Second point where f(x) is evaluated at.
 *            : fa       - f(a).
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

/*
 * Function   : bracket
 * Author     : Leo Werneck
 *
 * Given the current interval [a,b] and a new point c, adjusts the interval so
 * that it becomes either [a,c] or [c,b]. The point removed from the interval
 * is stored in d.
 *
 * Parameters : f        - The function f for which we wish to find the root.
 *            : fparams  - Possible parameters needed to evaluate f.
 *            : a        - Lower end of current interval.
 *            : b        - Upper end of current interval.
 *            : c        - New point in [a,b].
 *            : fa       - f(a).
 *            : fb       - f(b).
 *            : d        - Stores the point removed from [a,b].
 *            : fd       - f(d).
 *            : r        - Roots library parameters (see roots.h).
 *
 * Returns    : roots_error_t
 *                roots_success  - root was found.
 *                roots_continue - root not found; continue.
 */
// static inline roots_error_t
// bracket(
//     double f(const double, void *restrict),
//     void *restrict fparams,
//     double *restrict a,
//     double *restrict b,
//     const double c,
//     double *restrict fa,
//     double *restrict fb,
//     double *restrict d,
//     double *restrict fd,
//     roots_params *restrict r ) {

//   // Compute fc
//   double fc = f(c, fparams);

//   // Check for a zero
//   if( fc == 0.0 ) {
//     r->root = c;
//     r->residual = fc;
//     return (r->error_key = roots_success);
//   }

//   // Adjust the interval accordingly
//   if( (*fa)*fc < 0.0 ) {
//     // Replace b with c; store the old b in d
//     *d  = *b;
//     *fd = *fb;
//     *b  = c;
//     *fb = fc;
//   }
//   else {
//     // Replace a with c; store the old a in d
//     *d  = *a;
//     *fd = *fa;
//     *a  = c;
//     *fa = fc;
//   }
//   return roots_continue;
// }

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
