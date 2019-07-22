#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include "mintf.h"

int main(int argc, char* argv[]) {
   mintf("12345abcde %%=%\n");
   mintf("one: %d two: %x three: %b four: %c\n", 10, 10, 10, 'c');
   mintf("one: %c two: %b three: %x four: %d\n", 'h', 10, 10, 10);
   mintf("test string %s\n", "abcd hahaha123");
   mintf("test money %$ ___ %$\n", 123.567, -765.321);
   mintf("test money %$ ___ %$\n", 123.1, -3.19);
   mintf("test money %$ ___ %$\n", INT_MAX+0.1, INT_MIN-0.99);
   return EXIT_SUCCESS;
}
