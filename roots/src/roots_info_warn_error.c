#include "roots.h"

void
roots_info(const char *format, ...) {

  printf("(roots) ");

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

void
roots_Warn_Error(
      const char *type,
      const int exit_code,
      const char *filename,
      const int line,
      const char *funcname,
      const char *format,
      ...) {

  fprintf(stderr, "(roots) %s in file: %s, line: %d, function: %s\n", type, filename, line, funcname);
  fprintf(stderr, "(roots) %s message: ", type);

  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);

  switch (exit_code) {
  case roots_success:
    return;
    break;
  case roots_error_abort:
    abort();
    break;
  default:
    exit(exit_code);
    break;
  }
}
