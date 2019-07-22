#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mtat.h"
#include "bmp.h"
#include "miniunit.h"

int test_small_image_with_radius_2() {
    mu_start();
    const char* error = NULL;

    FILE* fp_1 = fopen("img1_6x6_color.bmp", "r");
    BMPImage* bmp_image_1 = read_bmp(fp_1, &error);
    BMPImage* monochrome1 = binarize(bmp_image_1, 2, 2, &error);
    mu_check(monochrome1 != NULL);
    FILE* fp_1_expected = fopen("img1_6x6_bw_r=02.bmp", "r");
    BMPImage* image_1_expected = read_bmp(fp_1_expected, &error);
    for(int data_test=0; data_test<120; data_test++) {
        mu_check(*(monochrome1 -> data + data_test) == *(image_1_expected -> data + data_test));
    }
    fclose(fp_1);
    fclose(fp_1_expected);
    free_bmp(bmp_image_1);
    free_bmp(monochrome1);
    free_bmp(image_1_expected);
    mu_end();
}

int test_small_image_with_radius_3() {
    mu_start();
    const char* error = NULL;

    FILE* fp_2 = fopen("img1_6x6_color.bmp", "r");
    BMPImage* bmp_image_2 = read_bmp(fp_2, &error);
    BMPImage* monochrome2 = binarize(bmp_image_2, 3, 2, &error);
    mu_check(monochrome2 != NULL);
    FILE* fp_2_expected = fopen("img1_6x6_bw_r=03.bmp", "r");
    BMPImage* image_2_expected = read_bmp(fp_2_expected, &error);
    for(int data_test=0; data_test<120; data_test++) {
        mu_check(*(monochrome2 -> data + data_test) == *(image_2_expected -> data + data_test));
    }
    fclose(fp_2);
    fclose(fp_2_expected);
    free_bmp(bmp_image_2);
    free_bmp(monochrome2);
    free_bmp(image_2_expected);
    mu_end();
}

int test_large_image_with_radius_20() {
    mu_start();
    const char* error = NULL;

    FILE* fp_3 = fopen("img2_384x510_gray.bmp", "r");
    BMPImage* bmp_image_3 = read_bmp(fp_3, &error);
    BMPImage* monochrome3 = binarize(bmp_image_3, 20, 5, &error);
    mu_check(monochrome3 != NULL);
    FILE* fp_3_expected = fopen("img2_384x510_bw_r=20.bmp", "r");
    BMPImage* image_3_expected = read_bmp(fp_3_expected, &error);
    for(int data_test=0; data_test<1200; data_test++) {
        mu_check(*(monochrome3 -> data + data_test) == *(image_3_expected -> data + data_test));
    }
    fclose(fp_3);
    fclose(fp_3_expected);
    free_bmp(bmp_image_3);
    free_bmp(monochrome3);
    free_bmp(image_3_expected);
    mu_end();
}

int test_huge_thread_number() {
    mu_start();
    const char* error = NULL;

    FILE* fp_4 = fopen("img1_6x6_color.bmp", "r");
    BMPImage* bmp_image_4 = read_bmp(fp_4, &error);
    BMPImage* monochrome4 = binarize(bmp_image_4, 2, 100, &error);
    mu_check(monochrome4 != NULL);
    FILE* fp_4_expected = fopen("img1_6x6_bw_r=02.bmp", "r");
    BMPImage* image_4_expected = read_bmp(fp_4_expected, &error);
    for(int data_test=0; data_test<120; data_test++) {
        mu_check(*(monochrome4 -> data + data_test) == *(image_4_expected -> data + data_test));
    }
    fclose(fp_4);
    fclose(fp_4_expected);
    free_bmp(bmp_image_4);
    free_bmp(monochrome4);
    free_bmp(image_4_expected);
    mu_end();
}

int test_with_one_thread() {
    mu_start();
    const char* error = NULL;

    FILE* fp_5 = fopen("img1_6x6_color.bmp", "r");
    BMPImage* bmp_image_5 = read_bmp(fp_5, &error);
    BMPImage* monochrome5 = binarize(bmp_image_5, 2, 1, &error);
    mu_check(monochrome5 != NULL);
    FILE* fp_5_expected = fopen("img1_6x6_bw_r=02.bmp", "r");
    BMPImage* image_5_expected = read_bmp(fp_5_expected, &error);
    for(int data_test=0; data_test<120; data_test++) {
        mu_check(*(monochrome5 -> data + data_test) == *(image_5_expected -> data + data_test));
    }
    fclose(fp_5);
    fclose(fp_5_expected);
    free_bmp(bmp_image_5);
    free_bmp(monochrome5);
    free_bmp(image_5_expected);
    mu_end();
}

int main(int argc, char* argv[]) {
    mu_run(test_small_image_with_radius_2);
    mu_run(test_small_image_with_radius_3);
    mu_run(test_large_image_with_radius_20);
    mu_run(test_huge_thread_number);
    mu_run(test_with_one_thread);
    return EXIT_SUCCESS;
}