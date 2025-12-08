/*
* Author: Ty Torres
* Date: 
* Goal: make a raytracer to learn some basics to graphics programming
*/

#include <filesystem>
#include <system_error>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

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

    //World information
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_w = 720;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    //Rendering the world
    cam.render(world);

    //actually generate image
    if (!stbi_write_png("output/A.png", cam.get_width(), cam.get_height(), cam.get_comp(), cam.get_img(), cam.get_width() * cam.get_comp())) {
        std::cerr << "Unable to create A.png" << '\n';
        return -1;
    }
    return 0;
}
