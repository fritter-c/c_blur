#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define BLUR_INTENSITY 200
int main(void){

    int width;
    int height;
    int channels;
    unsigned char *img = stbi_load("../purple-flower.jpg", &width, &height, &channels, 0);
    if (img == NULL){
        printf("error on load\n");
        exit(EXIT_FAILURE);
    }
    printf("image loaded width=%d, height=%d, channels=%d", width, height, channels);

    size_t img_size = width * height * channels;

    unsigned char *blurred_img = malloc(img_size);
    for(unsigned char *p = img + (channels * BLUR_INTENSITY / 2), *pb = blurred_img; p != img + img_size - ((BLUR_INTENSITY / 2)* channels); p += channels, pb += channels){
        stbi__uint32 pixel_r = 0;
        stbi__uint32 pixel_g = 0;
        stbi__uint32 pixel_b = 0;
        for (int i = 0; i < BLUR_INTENSITY / 2; i++){
            pixel_r += *(p + i * channels);
            pixel_g += *(p + 1 + i * channels);
            pixel_b += *(p + 2 + i * channels);     
        }
        for (int i = 0; i < BLUR_INTENSITY / 2; i++){
            pixel_r += *(p - i * channels);
            pixel_g += *(p + 1 - i * channels);
            pixel_b += *(p + 2 - i * channels);     
        }

        *pb = (uint8_t)((pixel_r)/BLUR_INTENSITY);  
        *(pb + 1) = (uint8_t)((pixel_g)/BLUR_INTENSITY);  
        *(pb + 2) = (uint8_t)((pixel_b)/BLUR_INTENSITY);  
    }
    stbi_write_jpg("grey-image.jpg", width, height, channels, blurred_img, 100);
    return EXIT_SUCCESS;
}