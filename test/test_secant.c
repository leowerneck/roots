#include "roots.h"

double f(void *params, const double x) {
  return (x-1.234)*(x+111);
}

int main() {

  roots_params r;
  r.iter_max = 300;
  r.ftol  = 1e-10;
  r.xtol  = 1e-10;
  roots_secant(f, NULL, 200, 0, &r);
  roots_info(&r);

  return r.error_key;
}
