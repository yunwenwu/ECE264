 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
   int check = 0;
   while(*(original+check) != '\0') {
      check ++;
   }
   check ++;
   char* string_dup = malloc(sizeof(*string_dup) * check);
   int counter = 0;

   while (*(original + counter)) {
      string_dup[counter] = *(original + counter);
      counter++;
   }

   string_dup[counter] = *(original + counter);
   return string_dup;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
