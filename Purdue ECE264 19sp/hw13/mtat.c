#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mtat.h"
#include "bmp.h"

typedef struct {
    unsigned char* data_origin;
    unsigned char* data_store;
    int row_below;
    int row_above;
    int radius;
    int image_width;
    int rows_to_process;
} WorkerArgs;

void* _convert_pixel(void* a_arg) {
    WorkerArgs* arg = (WorkerArgs*) a_arg;
    unsigned char* data_origin = arg -> data_origin;
    unsigned char* data_store = arg -> data_store;
    int row_below = arg -> row_below;
    int row_above = arg -> row_above;
    int radius = arg -> radius;
    int image_width = arg -> image_width;
    int rows_to_process = arg ->rows_to_process;
    int image_bytes_per_row = image_width * 3 + image_width % 4;
    int range_below, range_above, range_left, range_right;

    for(int i=0; i<rows_to_process; i++) {
        if(radius > (row_below+i)) {
            range_below = row_below + i;
        } else {
            range_below = radius;
        }

        if(radius > (row_above-i)) {
            range_above = row_above - i;
        } else {
            range_above = radius;
        }

        int* sum_of_brightness_on_column = malloc(sizeof(*sum_of_brightness_on_column) * image_width);
        int* pixel_brightness = malloc(sizeof(*pixel_brightness) * image_width);

        for(int j=0; j<image_width; j++) {
            pixel_brightness[j] = (int)(*(data_origin+0)) + (int)(*(data_origin+1)) + (int)(*(data_origin+2));

            sum_of_brightness_on_column[j] = 0;
            for(int pixel_dev = -1 * range_below; pixel_dev <= range_above; pixel_dev++) {
                sum_of_brightness_on_column[j] += (int)(*(data_origin+0+pixel_dev*image_bytes_per_row));
                sum_of_brightness_on_column[j] += (int)(*(data_origin+1+pixel_dev*image_bytes_per_row));
                sum_of_brightness_on_column[j] += (int)(*(data_origin+2+pixel_dev*image_bytes_per_row));
            }
            data_origin += 3;
        }
        data_origin += image_width % 4;

        for(int j=0; j<image_width; j++) {
            if(j<radius) {
                range_left = j;
            } else {
                range_left = radius;
            }
            if((image_width-j-1) < radius) {
                range_right = image_width-j-1;
            } else {
                range_right = radius;
            }

            int neighbour_brightness_total = 0;
            for(int column_in_range = j-range_left; column_in_range<(j+range_right+1); column_in_range++) {
                neighbour_brightness_total += sum_of_brightness_on_column[column_in_range];
            }
            
            if(pixel_brightness[j] * ((range_left+range_right+1)*(range_above+range_below+1)) <= neighbour_brightness_total) {
                *data_store = 0;
                data_store ++;
                *data_store = 0;
                data_store ++;
                *data_store = 0;
                data_store ++;
            } else {
                *data_store = 255;
                data_store ++;
                *data_store = 255;
                data_store ++;
                *data_store = 255;
                data_store ++;
            }
        }
        for(int k=0; k<(image_width % 4); k++) {
            *data_store = 0;
            data_store ++;
        }
        free(sum_of_brightness_on_column);
        free(pixel_brightness);
    }
    return NULL;
}

BMPImage* binarize(const BMPImage* image, int radius, int num_threads, const char** a_error) {  
    if(num_threads > image->header.height_px * image->header.width_px) {
        num_threads = image->header.height_px * image->header.width_px;
    }
	pthread_t* threads = malloc(num_threads * sizeof(*threads));
    WorkerArgs* a_arg = malloc(num_threads * sizeof(*a_arg));

    BMPImage* monochrome = malloc(sizeof(*monochrome));
    monochrome -> header = image -> header;
    monochrome -> data = malloc(monochrome -> header.image_size_bytes);

    int image_bytes_per_row = image->header.width_px * 3 + image->header.width_px % 4;
    int row_to_process = image -> header.height_px / num_threads;
    int thread_count;
	for(thread_count=0; thread_count<(num_threads-1); thread_count++) {
		a_arg[thread_count] = (WorkerArgs) {.data_origin = image->data + thread_count * image_bytes_per_row * row_to_process, 
                                            .data_store = monochrome->data + thread_count * image_bytes_per_row * row_to_process,
                                            .row_below = thread_count * row_to_process,
                                            .row_above = image->header.height_px - thread_count * row_to_process - 1,
                                            .radius = radius,
                                            .image_width = image->header.width_px,
                                            .rows_to_process = row_to_process
                                            };
	}

	a_arg[thread_count] = (WorkerArgs) {.data_origin = image->data + thread_count * image_bytes_per_row * row_to_process,
                                        .data_store = monochrome->data + thread_count * image_bytes_per_row * row_to_process,
                                        .row_below = thread_count * row_to_process,
                                        .row_above = image->header.height_px - thread_count * row_to_process - 1,
                                        .radius = radius,
                                        .image_width = image->header.width_px,
                                        .rows_to_process = image->header.height_px - thread_count * row_to_process
                                        };

    for(thread_count = 0; thread_count<num_threads; thread_count++) {
        pthread_create(&threads[thread_count], NULL, _convert_pixel, &a_arg[thread_count]);
    }
	for(thread_count = 0; thread_count < num_threads; thread_count++) {
        pthread_join(threads[thread_count], NULL);
    }
    free(threads);
    free(a_arg);
    return monochrome;
}