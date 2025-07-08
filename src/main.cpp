/*
* Author: Ty Torres
* Date: 
* Goal: make a raytracer to learn some basics to graphics programming
*/

#include <iostream>
#include <filesystem>
#include <system_error>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main ()
{
    //makes a directory to house all the images
    std::error_code ec;
    if (!std::filesystem::create_directory("output", ec)) {
        if (ec) {
            std::cerr << "Error: " << ec.message() << '\n';
            return -1;
        }
    }

    //dimensions of the image
    constexpr int nx = 300;
    constexpr int ny = 150;
    constexpr int comp = 4;
    uint8_t img[nx * ny * comp];

    //index for the images
    int k = 0;

    for (int j = ny - 1;  j >= 0; j--)
    {
        for (int i = 0; i < nx; i++) 
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.0f;
            img[k * comp] = int(255.99*r);                    // red channel
            img[k * comp + 1] = int(255.99*g);                // green channel
            img[k * comp + 2] = int(255.99*b);                // blue channel
            img[k * comp + 3] = 255;                          // alpha channel
            k++;
        }
    }

    if (!stbi_write_png("output/A.png", nx, ny, comp, img, nx * comp)) {
        std::cerr << "Unable to create A.png" << '\n';
    }
    return 0;
}
