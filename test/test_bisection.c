#include "roots.h"

double f(const double x, void *params) {
  return (x-1.234)*(x+111);
}

int main() {

  roots_params r;
  r.iter_max = 300;
  r.ftol  = 1e-10;
  r.xtol  = 1e-10;
  roots_bisection(f, NULL, 200, 0, &r);
  roots_info(&r);

  return r.error_key;
}
