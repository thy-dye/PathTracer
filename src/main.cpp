/*
* Author: Ty Torres
* Date: 12/9/2025
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
#include "material.h"
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

    auto material_ground = make_shared<lambertian>(color3(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color3(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.00 / 1.33);
    auto material_right = make_shared<metal>(color3(0.8, 0.6, 0.2), 3);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

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
