#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "miniunit.h"
#include "bmp.h"

BMPImage* create_bmp(size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b) {
    int image_size = h * (w * 3 + w % 4);
    int padding = w % 4;
    BMPImage* new_image = malloc(sizeof(BMPImage));

    new_image -> header.type = 0x4d42;
    new_image -> header.reserved1 = 0;
    new_image -> header.reserved2 = 0;
    new_image -> header.offset = 0x36;
    new_image -> header.dib_header_size = 0x28;
    new_image -> header.num_planes = 1;
    new_image -> header.bits_per_pixel = 0x18;
    new_image -> header.compression = 0;
    new_image -> header.x_resolution_ppm = 0;
    new_image -> header.y_resolution_ppm = 0;
    new_image -> header.num_colors = 0;
    new_image -> header.important_colors = 0;
    new_image -> header.width_px = w;
    new_image -> header.height_px = h;
    new_image -> header.image_size_bytes = image_size;
    new_image -> header.size = image_size + BMP_HEADER_SIZE;

    unsigned char* data = malloc(image_size * sizeof(*data));
    unsigned char* store_data = data;
    for(int row=0; row<h; row++) {
        for(int j=0; j<w; j++) {
            *store_data = b;
            store_data ++;
            *store_data = g;
            store_data ++;
            *store_data = r;
            store_data ++;
        }
        for(int pad_count = 0; pad_count<padding; pad_count++) {
            *store_data = 0;
            store_data ++;
        }
    }
    new_image -> data = data;
    return new_image;
}


void set_pixel(BMPImage* img, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
    int image_height = img->header.height_px;
    int image_width = img->header.width_px;
    int bytes_per_row = image_width * 3 + image_width % 4;

    unsigned char* change_pixel = img -> data;
    change_pixel += bytes_per_row * (image_height - y - 1) + 3 * x;
    *change_pixel = b;
    change_pixel ++;
    *change_pixel = g;
    change_pixel ++;
    *change_pixel = r;
    return;
}

int test_write() {
    mu_start();
    const char* error = NULL;

    FILE* fp = fopen("test_bmp.bmp", "w");
    BMPImage* new_image = create_bmp(50, 50, 0xff, 0x80, 0x0);

    mu_check(write_bmp(fp,new_image, &error));
    fclose(fp);
    free_bmp(new_image);
    mu_end();
}

int _check_normal_image(BMPImage* normal_image) {
    const char* error = NULL;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    fclose(fp);

    fp = fopen("corrupt_test_read.bmp", "r");
    BMPImage* result = read_bmp(fp, &error);
    fclose(fp);
    if(result == NULL) {
        return 0;
    } else {
        free_bmp(result);
        return 1;
    }
}

int _check_read_corrupt() {
    const char* error = NULL;
    FILE* fp = fopen("corrupt_test_read.bmp", "r");
    BMPImage* result = read_bmp(fp, &error);
    fclose(fp);
    if(result == NULL) {
        return 1;
    } else {
        free_bmp(result);
        return 0;
    }
}

int _check_height_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.height_px ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.height_px --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_width_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.width_px ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.width_px --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_type_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.type ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.type --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_size_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.size ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.size --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_offset_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.offset ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.offset --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_dib_header_size_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.dib_header_size ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.dib_header_size --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_num_planes_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.num_planes ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.num_planes --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_bits_per_pixel_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.bits_per_pixel ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.bits_per_pixel --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_compression_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.compression ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.compression --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_num_colors_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.num_colors ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.num_colors --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_important_colors_corrupt(BMPImage* normal_image) {
    const char* error = NULL;
    normal_image -> header.important_colors ++;
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    normal_image -> header.important_colors --;
    fclose(fp);
    return _check_read_corrupt();
}

int _check_data(BMPImage* normal_image) {
    const char* error = NULL;
    set_pixel(normal_image, 5, 29, 0x30, 0x70, 0xff);
    FILE* fp = fopen("corrupt_test_read.bmp", "w");
    write_bmp(fp, normal_image, &error);
    fclose(fp);

    fp = fopen("corrupt_test_read.bmp", "r");
    BMPImage* read_img = read_bmp(fp, &error);

    fseek(fp, 54, SEEK_SET);
    unsigned char* data = malloc(10 * sizeof(*data));
    fread(data, 1, 10, fp);
    fclose(fp);

    int result = 1;
    for(int i=0; i<10; i++) {
        if(data[i] != read_img->data[i]) {
            result = 0;
        }
    }

    if(read_img->data[15] != 0xff) {
        result = 0;
    } else if(read_img->data[16] != 0x70) {
        result = 0;
    } else if(read_img->data[17] != 0x30) {
        result = 0;
    }
    free_bmp(read_img);
    free(data);
    return result;
}

int test_read() {
    mu_start();
    BMPImage* normal_image = create_bmp(30, 30, 0xff, 0x80, 0x30);

    mu_check(_check_normal_image(normal_image));
    mu_check(_check_height_corrupt(normal_image));
    mu_check(_check_width_corrupt(normal_image));
    mu_check(_check_type_corrupt(normal_image));
    mu_check(_check_size_corrupt(normal_image));
    mu_check(_check_offset_corrupt(normal_image));
    mu_check(_check_dib_header_size_corrupt(normal_image));
    mu_check(_check_num_planes_corrupt(normal_image));
    mu_check(_check_bits_per_pixel_corrupt(normal_image));
    mu_check(_check_compression_corrupt(normal_image));
    mu_check(_check_num_colors_corrupt(normal_image));
    mu_check(_check_important_colors_corrupt(normal_image));
    mu_check(_check_data(normal_image));

    free_bmp(normal_image);
    mu_end();
}

int test_crop() {
    mu_start();
    const char* error = NULL;

    BMPImage* normal_image = create_bmp(8, 8, 0x50, 0x80, 0x80);
    set_pixel(normal_image, 0, 5, 0x30, 0x40, 0x60);
    BMPImage* crop_image = crop_bmp(normal_image, 0, 0, 6, 6, &error);

    if(crop_image != NULL) {
        mu_check(normal_image->data[48] == crop_image->data[0]);
        mu_check(normal_image->data[49] == crop_image->data[1]);
        mu_check(normal_image->data[50] == crop_image->data[2]);
        mu_check(normal_image->data[51] == crop_image->data[3]);
        free_bmp(crop_image);
    } else {
        mu_check(crop_image != NULL);
    }
    free_bmp(normal_image);
    mu_end();
}

int main(int argc, char* argv[]) {
    mu_run(test_write);
    mu_run(test_read);
    mu_run(test_crop);
    return EXIT_SUCCESS;
}