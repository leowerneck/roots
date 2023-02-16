#ifndef ROOTS_UTILS_H_
#define ROOTS_UTILS_H_

static inline void
swap(
    double *restrict a,
    double *restrict b ) {

  const double c = *a;
  *a = *b;
  *b = c;
}

#endif // ROOTS_UTILS_H_
