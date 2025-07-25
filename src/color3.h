#ifndef COLOR_H 
#define COLOR_H

#include "vec3.h"

using color3 = vec3;

void write_color(unsigned char* img, const int &comp, const int &pixel_index, const color3 &pixel_color) {
            img[pixel_index * comp] = int(255.99 * pixel_color.r());                    // red channel
            img[pixel_index * comp + 1] = int(255.99 * pixel_color.g());                // green channel
            img[pixel_index * comp + 2] = int(255.99 * pixel_color.b());                // blue channel
            img[pixel_index * comp + 3] = 255;                                          // alpha channel
    }

#endif