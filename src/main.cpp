#include <iostream>
#include <filesystem>
#include <system_error>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main ()
{
    std::error_code ec;
    if (!std::filesystem::create_directory("output", ec)) {
        if (ec) {
            std::cerr << "Error: " << ec.message() << '\n';
        }
    }

    constexpr int nx = 300;
    constexpr int ny = 150;
    for (int j = ny - 1;  j >= 0; j--)
    {
        for (int i = 0; i < nx; i++) 
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.0f;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
        }
    }
    return 0;
}
