#include "roots.h"

double f(const double x, void *params) {
  return (x-1.234)*(x+111);
}

int main() {

  roots_params r;
  r.iter_max = 300;
  r.tol  = 1e-10;
  roots_false_position(f, NULL, 200, 0, &r);
  roots_info(&r);

  return r.error_key;
}
