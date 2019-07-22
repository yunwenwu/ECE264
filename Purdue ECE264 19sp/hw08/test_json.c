#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"


int main(int argc, char* argv[]){
    Element element1;
    Element element2;
    Element element3;
    Element element4;
    Element element5;
    Element element6;
    Element element7;
    Element element8;

    char* pos1 = "   -123ABC";
    char* pos2 = "-A99";
    char* pos3 = " \n 89+32";
    char* pos4 = "[\"H\", 23]";
    char* pos5 = "[]";
    char* pos6 = "[[1,3]";
    char* pos7 = "[2,4]]";
    char* pos8 = "[3,4,[\"A\"],\"ff\",[123,456], 6,7]";

    bool test_result1 = parse_element(&element1, &pos1);
    if(test_result1 == true) {
        printf("test1 passed\n");
        print_element(element1);
        printf("\n");
    } else {
        printf("test1 failed\n");
    }

    bool test_result2 = parse_element(&element2, &pos2);
    if(test_result2 == true) {
        printf("test2 passed\n");
        print_element(element2);
        printf("\n");
    } else {
        printf("test2 failed\n");
    }

    bool test_result3 = parse_element(&element3, &pos3);
    if(test_result3 == true) {
        printf("test3 passed\n");
        print_element(element3);
        printf("\n");
    } else {
        printf("test3 failed\n");
    }

    bool test_result4 = parse_element(&element4, &pos4);
    if(test_result4 == true) {
        printf("test4 passed\n");
        print_element(element4);
        printf("\n");
    } else {
        printf("test4 failed\n");
    }

    bool test_result5 = parse_element(&element5, &pos5);
    if(test_result5 == true) {
        printf("test5 passed\n");
        print_element(element5);
        printf("\n");
    } else {
        printf("test5 failed\n");
    }

    bool test_result6 = parse_element(&element6, &pos6);
    if(test_result6 == true) {
        printf("test6 passed\n");
        print_element(element6);
        printf("\n");
    } else {
        printf("test6 failed\n");
    }

    bool test_result7 = parse_element(&element7, &pos7);
    if(test_result7 == true) {
        printf("test7 passed\n");
        print_element(element7);
        printf("\n");
    } else {
        printf("test7 failed\n");
    }

    bool test_result8 = parse_element(&element8, &pos8);
    if(test_result8 == true) {
        printf("test8 passed\n");
        print_element(element8);
        printf("\n");
    } else {
        printf("test8 failed\n");
    }
    free_element(element4);
    free_element(element5);
    free_element(element6);
    free_element(element7);
    free_element(element8);
    return EXIT_SUCCESS;
}
