#include "clog.h"
#include <unistd.h>

#ifndef __miniunit_h__
#define __miniunit_h__

#define mu_start() \
int __mu_line_number = 0

#define mu_check(condition) \
if((condition) != 1) {__mu_line_number = __LINE__;}

#define mu_run(function) \
if(function() == 0) { \
   if(isatty(STDOUT_FILENO)) { \
      fprintf(stderr, "%s", ANSI_GREEN); \
      fprintf(stderr, "Test passed: (%s)\n", #function); \
      fprintf(stderr, "%s", ANSI_RESET); \
   } \
   else { \
      printf("Test passed: (%s)\n", #function); \
   } \
} \
else { \
   if(isatty(STDOUT_FILENO)) { \
      fprintf(stderr, "%s", ANSI_RED); \
      fprintf(stderr, "Test failed: (%s) at line %d\n", #function, function()); \
      fprintf(stderr, "%s", ANSI_RESET); \
   } \
   else { \
      printf("Test failed: (%s) at line %d\n", #function, function()); \
   } \
}

#define mu_end() \
return __mu_line_number

#endif
