#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include "mintf.h"

void print_digit(int digit) {
   if(digit < 10) {
       fputc('0' + digit, stdout);
   } else {
       fputc('a' + digit - 10, stdout);
   }
}

void print_integer(int n, int radix, char* prefix) {
   unsigned int abs_value = 0;
   if (n < 0) {
      fputc('-', stdout);
      abs_value = -n;
   } else {
      abs_value = n;
   }
   
   while (* prefix) {
      fputc(* prefix, stdout);
      prefix += 1; 
   }
   
   if(abs_value >= radix) {
      print_integer(abs_value/radix, radix, "");
   }
   print_digit(abs_value % radix);
   return;
}

void mintf(const char *format, ...) {
   va_list num_input;
   va_start(num_input, format);

   while(* format) {
      if(* format != '%') {
         fputc(* format, stdout);
      } else {
         char symbol = *(format + 1);
         if (symbol == 0) {
            fputc('%', stdout);
         } else if(symbol == 'd') {
            print_integer(va_arg(num_input, int), 10, "");
            format ++;
         } else if(symbol == 'x') {
            print_integer(va_arg(num_input, int), 16, "0x");
            format ++;
         } else if(symbol == 'b') {
            print_integer(va_arg(num_input, int), 2, "0b");
            format ++;
         } else if(symbol == '$') {
	double money = va_arg(num_input, double);
	int int_part = (int) money;
	print_integer(int_part, 10, "$");
	fputc('.', stdout);
	long long int decimal_part = money * 100 - int_part * 100;

	if (decimal_part >= 0 && decimal_part < 10) {
	   print_integer(decimal_part, 10, "0");
	} else if (decimal_part >= 10) {
	   print_integer(decimal_part, 10, "");
	} else if (decimal_part < 0 && decimal_part > -10) {
	   print_integer(-decimal_part, 10, "0");
	} else if (decimal_part <= -10) {
	   print_integer(-decimal_part, 10, "");
	}

            format ++;
         } else if(symbol == 's') {
            char* strings = va_arg(num_input, char*);
	while(* strings) {
	   fputc(* strings, stdout);
	   strings ++;
	}
            format ++;
         } else if(symbol == 'c') {
            fputc(va_arg(num_input, int), stdout);
            format ++;
         } else if(symbol == '%') {
            fputc('%', stdout);
            format ++;
         } else {
            fputc('%', stdout);
         }
      }
      format ++;
   }
   va_end(num_input);
   return;
}