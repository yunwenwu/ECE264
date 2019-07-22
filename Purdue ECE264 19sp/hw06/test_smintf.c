#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "smintf.h"

int main(int argc, char** argv) {
   char* text1 = smintf("12345abcde %%=%\n");
   printf("%s", text1);
   free(text1);

   char* text2 = smintf("one: %d two: %x three: %b four: %c\n", -10, -10, -10, 'c');
   printf("%s", text2);
   free(text2);

   char* text3 = smintf("one: %c two: %b three: %x four: %d\n", 'h', 10, 10, 10);
   printf("%s", text3);
   free(text3);

   char* text4 = smintf("test string %s\n", "abcd hahaha123");
   printf("%s", text4);
   free(text4);

   char* text5 = smintf("%d\n", 234);
   printf("%s", text5);
   free(text5);

   char* text6 = smintf("%x\n", 314);
   printf("%s", text6);
   free(text6);

   char* text7 = smintf("test money %$ ___ %$\n", 123.567, -765.321);
   printf("%s", text7);
   free(text7);

   char* text8 = smintf("test money %$ ___ %$\n", 123.1, -3.19);
   printf("%s", text8);
   free(text8);

   return EXIT_SUCCESS;
}
