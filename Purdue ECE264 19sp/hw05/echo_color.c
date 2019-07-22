#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "clog.h"

int main(int argc, char* argv[]) {
   if(argc != 3) {
      printf("Usage: %%s <\"red\"|\"green\"|\"yellow\"|\"blue\"|\"magenta\"|\"cyan\"> STRING...");
      return EXIT_FAILURE;
   }

   if(strcmp(argv[1], "red") == 0) {
      if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_RED);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }

   } else if(strcmp(argv[1], "green") == 0) {
      if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_GREEN);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }

   } else if(strcmp(argv[1], "yellow") == 0) {
       if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_YELLOW);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }

   } else if(strcmp(argv[1], "blue") == 0) {
      if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_BLUE);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }

   } else if(strcmp(argv[1], "magenta") == 0) {
      if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_MAGENTA);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }
   } else if(strcmp(argv[1], "cyan") == 0) {
      if(isatty(STDOUT_FILENO)) {
         fprintf(stderr, "%s", ANSI_CYAN);
         fprintf(stderr, "%s", argv[2]);
         fprintf(stderr, "%s", ANSI_RESET);
      } else {
         printf("%s\n", argv[2]);
      }

   } else {
      printf("Usage: %%s <\"red\"|\"green\"|\"yellow\"|\"blue\"|\"magenta\"|\"cyan\"> STRING...");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
