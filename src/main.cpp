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
#include "vec3.h"

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

    //index for the image
    int pixel_index = 0;

    for (int j = ny - 1;  j >= 0; j--)
    {
        for (int i = 0; i < nx; i++) 
        {
            color3 pixel_color = color3(double(i) / double(nx), double(j) / double(ny), 0.0);
            img[pixel_index * comp] = int(255.99 * pixel_color.r());                    // red channel
            img[pixel_index * comp + 1] = int(255.99 * pixel_color.g());                // green channel
            img[pixel_index * comp + 2] = int(255.99 * pixel_color.b());                // blue channel
            img[pixel_index * comp + 3] = 255;                                          // alpha channel
            pixel_index++;
        }
    }

    //actually generate image
    if (!stbi_write_png("output/A.png", nx, ny, comp, img, nx * comp)) {
        std::cerr << "Unable to create A.png" << '\n';
        return -1;
    }
    return 0;
}
