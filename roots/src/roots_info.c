#include "roots.h"

/*
 * Function   : roots_info
 * Author     : Leo Werneck
 *
 * Prints information about the root-finding process.
 *
 * Parameters : r        - Pointer to roots library parameters (see roots.h).
 *
 * Returns    : Nothing.
 */
void
roots_info(const roots_params *restrict r) {

  // Step 1: Print basic message to the user
  printf("(roots) Root-finding information:\n");
  printf("(roots)   %16s : %s\n", "Method", r->method);
  printf(
        "(roots)   %16s : [%c%21.15e, %c%21.15e]\n",
        "Initial interval",
        r->a >= 0 ? '+' : '-',
        fabs(r->a),
        r->b >= 0 ? '+' : '-',
        fabs(r->b));
  printf("(roots)   %16s : ", "Status");
  switch(r->error_key) {
    case roots_continue:
      break;
    case roots_success:
      printf("Success\n");
      break;
    case roots_error_root_not_bracketed:
      printf("Failure\n");
      printf("(roots)   %16s : ", "Error message");
      printf("Initial interval does not bracket the root.\n");
      break;
    case roots_error_max_iter:
      printf("Failure\n");
      printf("(roots)   %16s : ", "Error message");
      printf("Maximum number of iterations (%d) exceeded.\n", r->max_iters);
      break;
  }

  // Step 2: If succeeded, print detailed success message
  if(!r->error_key) {
    printf("(roots)   %16s : %d\n", "Iterations", r->n_iters);
    printf("(roots)   %16s : %.15e\n", "Root", r->root);
    printf("(roots)   %16s : %.15e\n", "Residual", r->residual);
  }
}
