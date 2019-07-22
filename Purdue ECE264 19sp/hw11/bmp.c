#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

BMPImage* read_bmp(FILE* fp, const char** a_error) {
    if(fp == NULL || ferror(fp)) {
        *a_error = strerror(errno);
        return NULL;
    }
	fseek(fp, 0, SEEK_END);

	int image_size = ftell(fp);
    if(image_size < 54) {
        *a_error = "document too short";
        return NULL;
    }
	int data_size = image_size - BMP_HEADER_SIZE;

	fseek(fp, 0, SEEK_SET);
    if(ferror(fp)) {
        *a_error = strerror(errno);
        return NULL;
    }

	BMPImage* B_M_P= malloc(sizeof(*B_M_P));
    if(B_M_P == NULL) {
        *a_error = "No heap space: malloc fail";
        return NULL;
    }
    unsigned char* data = malloc(sizeof(*B_M_P->data)*data_size);
    if(data == NULL) {
        *a_error = "No heap space: malloc fail";
        free(B_M_P);
        return NULL;
    }

	if(!fread(&B_M_P->header, sizeof(B_M_P->header), 1, fp)) {
        *a_error = strerror(errno);
        free(B_M_P);
        free(data);
        return NULL;
    }
    if(!fread(data, data_size, 1, fp)) {
        *a_error = strerror(errno);
        free(B_M_P);
        free(data);        
        return NULL;
    }
    B_M_P -> data = data;

    if(!check_bmp_header(&B_M_P->header, fp)) {
        *a_error = "header is incorrect";
        free(B_M_P);
        free(data);
        return NULL;
    }

    *a_error = NULL;
	return B_M_P;
}

bool check_bmp_header(const BMPHeader* bmp_hdr, FILE* fp) {
	if(bmp_hdr->type!=0x4d42) {
		return false;
	} else if(bmp_hdr->offset!=BMP_HEADER_SIZE) {
		return false;
	} else if(bmp_hdr->dib_header_size!=DIB_HEADER_SIZE) {
		return false;
	} else if(bmp_hdr->num_planes!=1) {
		return false;
	} else if(bmp_hdr->compression!=0) {
		return false;
	} else if(bmp_hdr->important_colors!=0 || bmp_hdr->num_colors!=0) {
		return false;
	} else if(bmp_hdr->bits_per_pixel!=24) {
		return false;
	} else if(bmp_hdr->size-bmp_hdr->image_size_bytes!=54) {
		return false;
	}
	int bytes_per_row = bmp_hdr -> width_px * 3 + bmp_hdr -> width_px % 4;
	if(bytes_per_row * bmp_hdr -> height_px != bmp_hdr -> image_size_bytes) {
        return false;
    }

    fseek(fp, 0, SEEK_END);
    int file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(file_length != bmp_hdr->size) {
        return false;
    }

    return true;
}

bool write_bmp(FILE* fp, BMPImage* image, const char** a_error) {
    int data_length = image -> header.image_size_bytes;
    if(fp == NULL || ferror(fp)) {
        *a_error = strerror(errno);
        return false;
    }
    if(image == NULL) {
        *a_error = "BMPimage is empty";
        return false;
    }
    fwrite(&image->header, sizeof(BMPHeader), 1, fp);
    if(ferror(fp)) {
        *a_error = strerror(errno);
        return false;
    }
    fwrite(image->data, sizeof(*image->data), data_length, fp);
    if(ferror(fp)) {
        *a_error = strerror(errno);
        return false;
    }
    *a_error = NULL;
    return true;
}

void free_bmp(BMPImage* image) {
    free(image->data);
    free(image);
    return;
}

BMPImage* crop_bmp(const BMPImage* image, int x, int y, int w, int h, const char** a_error) {
    int bytes_per_row = w * 3 + w % 4;
    int image_size = h * bytes_per_row;
    if(image == NULL) {
        *a_error = "image is empty";
        return NULL;
    }
    
    BMPImage* new_image = malloc(sizeof(BMPHeader) + image_size);
    if(new_image == NULL) {
        *a_error = "malloc fail";
        return NULL;
    }

    new_image -> header.type = image -> header.type;
    new_image -> header.reserved1 = image -> header.reserved1;
    new_image -> header.reserved2 = image -> header.reserved2;
    new_image -> header.offset = image -> header.offset;
    new_image -> header.dib_header_size = image -> header.dib_header_size;
    new_image -> header.num_planes = image -> header.num_planes;
    new_image -> header.bits_per_pixel = image -> header.bits_per_pixel;
    new_image -> header.compression = image -> header.compression;
    new_image -> header.x_resolution_ppm = image -> header.x_resolution_ppm;
    new_image -> header.y_resolution_ppm = image -> header.y_resolution_ppm;
    new_image -> header.num_colors = image -> header.num_colors;
    new_image -> header.important_colors = image -> header.important_colors;
    new_image -> header.width_px = w;
    new_image -> header.height_px = h;
    new_image -> header.image_size_bytes = image_size;
    new_image -> header.size = image_size + BMP_HEADER_SIZE;

    int original_width = image->header.width_px;
    int original_height = image->header.height_px;
    int original_bytes_per_row = original_width * 3 + original_width % 4;
    new_image -> data = malloc(new_image -> header.image_size_bytes);
    unsigned char* store_data = new_image -> data;
    unsigned char* read_data = image -> data;

    read_data += (original_height-y-h) * original_bytes_per_row;
    for(int i = 0; i < h; i++) {
        read_data += 3 * x;
        for(int j = 0; j < 3 * w; j++) {
            *store_data = *read_data;
            store_data ++;
            read_data ++;
        }
        for(int k = 0; k < w % 4; k++) {
            *store_data = 0;
            store_data ++;
        }
        for(int l = 0; l < original_bytes_per_row - 3 * (x+w); l++) {
            read_data ++;
        }
    }
    *a_error = NULL;
    return new_image;
}