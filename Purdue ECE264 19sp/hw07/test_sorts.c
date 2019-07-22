#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorts.h"

int main(int argc, char* argv[]) {
    int array1[] = {72, 1231, 521, 33, 12, 413, 124, 123, 122, 99898, 223};
    merge_sort_array(array1, 11);
    for(int i = 0; i < 11 ; i++) {
        printf("%d ", array1[i]);
    }
    printf("\n");

    int array2[] = {72, 1231, 521, 33, 12, 413, 124, 123, 122, 99898, 223};
    quick_sort_array(array2, 11);
    for(int i = 0; i < 11 ; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    int array3[] = {72, 1231, 521, 33, 12, 413, 124, 123, 122, 99898, 223};
    tree_sort_array(array3, 11);
    for(int i = 0; i < 11 ; i++) {
        printf("%d ", array3[i]);
    }

    return EXIT_SUCCESS;
}