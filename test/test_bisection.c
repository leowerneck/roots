#include "roots.h"

double f(void *params, const double x) {
  return x*x - 1.234;
}

int main() {

  roots_params r;
  r.itmax = 300;
  r.ftol  = 1e-10;
  r.xtol  = 1e-10;
  const double root = roots_bisection(f, NULL, 2, 0, &r);
  roots_info("Found root at x  : %.15e\n", root);
  roots_info("Residual at root : %.15e\n", f(NULL, root));

  return 0;
}
