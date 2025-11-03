#ifndef COLOR_H 
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color3 = vec3;

//color the image with given pixel_color
void write_color(unsigned char* img, const int &comp, const int &pixel_index, const color3 &pixel_color) {
        auto r = pixel_color.r();
        auto g = pixel_color.g();
        auto b = pixel_color.b();

        static const interval intensity(0, 0.999);
        img[pixel_index * comp] = int(255.99 * intensity.clamp(r));                    // red channel
        img[pixel_index * comp + 1] = int(255.99 * intensity.clamp(g));                // green channel
        img[pixel_index * comp + 2] = int(255.99 * intensity.clamp(b));                // blue channel
        img[pixel_index * comp + 3] = 255;                                             // alpha channel
    }

#endif