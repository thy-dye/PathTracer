#ifndef COLOR_H 
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color3 = vec3;

inline double linear_to_gamma(double linear_component){
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0;
}

//color the image with given pixel_color
void write_color(unsigned char* img, const int &comp, const int &pixel_index, const color3 &pixel_color) {
        auto r = pixel_color.r();
        auto g = pixel_color.g();
        auto b = pixel_color.b();

        //turn rgb linear space to gamma space
        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        //translate [0,1] range of components to [0,255]
        static const interval intensity(0, 0.999);
        img[pixel_index * comp] = int(255.99 * intensity.clamp(r));                    // red channel
        img[pixel_index * comp + 1] = int(255.99 * intensity.clamp(g));                // green channel
        img[pixel_index * comp + 2] = int(255.99 * intensity.clamp(b));                // blue channel
        img[pixel_index * comp + 3] = 255;                                             // alpha channel
    }

#endif