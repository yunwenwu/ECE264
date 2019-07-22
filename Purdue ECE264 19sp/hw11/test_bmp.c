#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

int main(int argc, char* argv[]) {
    const char* error = NULL;
    
    FILE* image_1 = fopen("airplane.bmp", "r");
    if(image_1 == NULL || ferror(image_1)) {
        error = strerror(errno);
    }
    else{
        BMPImage* bmp_image_1 = read_bmp(image_1, &error);
        if(bmp_image_1 != NULL) {
            BMPImage* crop_image_1 = crop_bmp(bmp_image_1, 200, 200, 200, 200, &error);
            if(crop_image_1!=NULL) {
                FILE* image_1_result = fopen("cropped_airplane.bmp", "w");
                write_bmp(image_1_result, crop_image_1, &error);    
                free_bmp(crop_image_1);
	    fclose(image_1_result);
            }
            free_bmp(bmp_image_1);
        }
    }
    fclose(image_1);




    FILE* image_2 = fopen("corrupt_airplanei.bmp", "r");
    if(image_2 == NULL || ferror(image_2)) {
        error = strerror(errno);
    }
    else{
        BMPImage* bmp_image_2 = read_bmp(image_2, &error);
        if(bmp_image_2 != NULL) {
            BMPImage* crop_image_2 = crop_bmp(bmp_image_2, 100, 100, 100, 100, &error);
            if(crop_image_2!=NULL) {
                FILE* image_2_result = fopen("fail_cropped_airplane.bmp", "w");
                write_bmp(image_2_result, crop_image_2, &error);    
                free_bmp(crop_image_2);
	    fclose(image_2_result);
            }
            free_bmp(bmp_image_2);
        }
    }
    fclose(image_2);

    FILE* image_3 = fopen("green_earth.bmp", "r");
    if(image_3 == NULL || ferror(image_3)) {
        error = strerror(errno);
    }
    else{
        BMPImage* bmp_image_3 = read_bmp(image_3, &error);
        if(bmp_image_3 != NULL) {
            BMPImage* crop_image_3 = crop_bmp(bmp_image_3, 100, 100, 100, 100, &error);
            if(crop_image_3!=NULL) {
                FILE* image_3_result = fopen("cropped_green_earth.bmp", "w");
                write_bmp(image_3_result, crop_image_3, &error);    
                free_bmp(crop_image_3);
	    fclose(image_3_result);
            }
            free_bmp(bmp_image_3);
        }
    }
    fclose(image_3);

    FILE* image_4 = fopen("corrupt_green_earthh.bmp", "r");
    if(image_4 == NULL || ferror(image_4)) {
        error = strerror(errno);
    }
    else{
        BMPImage* bmp_image_4 = read_bmp(image_4, &error);
        if(bmp_image_4 != NULL) {
            BMPImage* crop_image_4 = crop_bmp(bmp_image_4, 100, 100, 100, 100, &error);
            if(crop_image_4!=NULL) {
                FILE* image_4_result = fopen("fail_cropped_green_earth.bmp", "w");
                write_bmp(image_4_result, crop_image_4, &error);    
                free_bmp(crop_image_4);
	    fclose(image_4_result);
            }
            free_bmp(bmp_image_4);
        }
    }
    fclose(image_4);

    FILE* image_5 = fopen("gray_earth.bmp", "r");
    if(image_5 == NULL || ferror(image_5)) {
        error = strerror(errno);
    }
    else{
        BMPImage* bmp_image_5 = read_bmp(image_5, &error);
        if(bmp_image_5 != NULL) {
            BMPImage* crop_image_5 = crop_bmp(bmp_image_5, 100, 100, 100, 100, &error);
            if(crop_image_5!=NULL) {
                FILE* image_5_result = fopen("cropped_gray.bmp", "w");
                write_bmp(image_5_result, crop_image_5, &error);    
                free_bmp(crop_image_5);
	    fclose(image_5_result);
            }
            free_bmp(bmp_image_5);
        }
    }
    fclose(image_5);
    return EXIT_SUCCESS;
}