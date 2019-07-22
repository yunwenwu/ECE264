#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

void _store_number(int n, int radix, char* prefix, int* a_count, char* str_in_heap) {
    unsigned int abs_value = 0;
    if (n < 0) {
        str_in_heap[*a_count] = '-';
        (*a_count) ++;
        abs_value = -n;
    } else {
        abs_value = n;
    }
   
    while (* prefix) {
        str_in_heap[*a_count] = *prefix;
        (*a_count) ++;
        prefix ++; 
    }
   
    if(abs_value >= radix) {
        _store_number(abs_value/radix, radix, "", a_count, str_in_heap);
    }

    if(abs_value % radix < 10) {
        str_in_heap[*a_count] = '0' + abs_value % radix;
    } else {
        str_in_heap[*a_count] = 'a' + abs_value % radix - 10;
    }
    (*a_count) ++;
    return;
}


int _check_length_of_number(int number, int base) {
    int length = 0;
    
    if (number <= 0) {
        length ++;
    }
    while(number != 0){
        number /= base;
        length ++;
    }
    return length;
}

char* smintf(const char* format, ...) {
    /* check the length of malloc */
    va_list check_input;
    va_start(check_input, format);
    int length = 0;
    int order = 0;
    while(* (format + order)) {
        if(* (format + order) != '%') {
            length ++;
        } else {
            char test_symbol = *(format + order + 1);
            if (test_symbol == '\0') {
                length ++;
            } else if(test_symbol == 'd') {
                length += _check_length_of_number(va_arg(check_input, int), 10);
                order ++;
            } else if(test_symbol == 'x') {
                length += _check_length_of_number(va_arg(check_input, int), 16);
                length += 2;
                order ++;
            } else if(test_symbol == 'b') {
                length += _check_length_of_number(va_arg(check_input, int), 2);
                length += 2;
                order ++;
            } else if(test_symbol == '$') {
                length += _check_length_of_number(((int)va_arg(check_input, double)), 10);
                length += 4;
                order ++;
            } else if(test_symbol == 's') {
                char* strings = va_arg(check_input, char*);
	            while(* strings) {
	                length ++;
	                strings ++;
	            }
                order ++;
            } else if(test_symbol == 'c') {
                va_arg(check_input, int);

                length ++;
                order ++;
            } else if(test_symbol == '%') {
                length ++;
                order ++;
            } else {
                length ++;
            }
        }
    order ++;
    }
    va_end(check_input);
    length ++;
    /* length of malloc is now stored in length */

    va_list num_input;
    va_start(num_input, format);

    char* str_in_heap = malloc(length * sizeof(*str_in_heap));
    if (str_in_heap == NULL) {
        return NULL;
    }
    
    int count = 0;
    int* a_count = &count;
    while(* format) {
        if(* format != '%') {
            str_in_heap[count] = *format;
            count ++;
        } else {
            char symbol = *(format + 1);
            if (symbol == '\0') {
                str_in_heap[count] = '%';
                count ++;
            } else if(symbol == 'd') {
                _store_number(va_arg(num_input, int), 10, "", a_count, str_in_heap);
                format ++;
            } else if(symbol == 'x') {
                _store_number(va_arg(num_input, int), 16, "0x", a_count, str_in_heap);
                format ++;
            } else if(symbol == 'b') {
                _store_number(va_arg(num_input, int), 2, "0b", a_count, str_in_heap);
                format ++;
            } else if(symbol == '$') {
	            double money = va_arg(num_input, double);
	            int int_part = (int) money;
                _store_number(int_part, 10, "$", a_count, str_in_heap);
                str_in_heap[count] = '.';
                count ++;
	            long long int decimal_part = money * 100 - int_part * 100;
	            if (decimal_part >= 0 && decimal_part < 10) {
                    _store_number(decimal_part, 10, "0", a_count, str_in_heap);
	            } else if (decimal_part >= 10) {
                    _store_number(decimal_part, 10, "", a_count, str_in_heap);
	            } else if (decimal_part < 0 && decimal_part > -10) {
                    _store_number(-decimal_part, 10, "0", a_count, str_in_heap);
	            } else if (decimal_part <= -10) {
                    _store_number(-decimal_part, 10, "", a_count, str_in_heap);
	            }
                format ++;
            } else if(symbol == 's') {
                char* string2 = va_arg(num_input, char*);
	            while(*string2) {
                    str_in_heap[count] = *string2;
                    count ++;
                    string2 ++;
	            }
                format ++;
            } else if(symbol == 'c') {
                char va_char = va_arg(num_input, int);
                str_in_heap[count] = va_char;
                count ++;
                format ++;
            } else if(symbol == '%') {
                str_in_heap[count] = '%';
                count ++;
                format ++;
            } else {
                str_in_heap[count] = '%';
                count ++;
            }
        }
    format ++;
    }
    str_in_heap[count] = '\0';
    va_end(num_input);
    return str_in_heap;
}