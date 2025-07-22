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
#include "ray.h"



void write_color(unsigned char* img, const int &comp, const int &pixel_index, const color3 &pixel_color) {
            img[pixel_index * comp] = int(255.99 * pixel_color.r());                    // red channel
            img[pixel_index * comp + 1] = int(255.99 * pixel_color.g());                // green channel
            img[pixel_index * comp + 2] = int(255.99 * pixel_color.b());                // blue channel
            img[pixel_index * comp + 3] = 255;                                          // alpha channel
    }

double hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc =center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), oc);
    double c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant))/(2.0 * a);
    }
}

color3 ray_color(const ray& r) {
    double t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color3(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color3(1.0, 1.0, 1.0) + a*color3(0.5, 0.7, 1.0);
}

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
    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_w = 720;
    constexpr int image_h = (int(image_w / aspect_ratio) < 1) ? 1 : int(image_w / aspect_ratio);
    constexpr int comp = 4;
    uint8_t img[image_w * image_h * comp];

    //index for the image
    int pixel_index = 0;

    //camera & viewport
    double focal_length = 1.0;
    double viewport_h = 2.0;
    double viewport_w = viewport_h * (double(image_w)/image_h);
    point3 camera_center = point3(0, 0, 0);

    // Vectors that span the entire viewport
    vec3 viewport_u = vec3(viewport_w, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_h, 0);

    //delta for each pixel that scales to the image
    vec3 pixel_delta_u = viewport_u / image_w;
    vec3 pixel_delta_v = viewport_v / image_h;

    //vector 
    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "Image Dimensions: " << image_w << " " << image_h << "\n";


    //rendering section
    for (int j = 0;  j < image_h; j++)
    {
        std::clog << "Scanlines remaining: " << (image_h - j) << " \n" << std::flush;

        for (int i = 0; i < image_w; i++) 
        {
            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;

            ray r = ray(camera_center, ray_direction);

            color3 pixel_color = ray_color(r);
            
            write_color(img, comp, pixel_index, pixel_color);
            pixel_index++;
        }
    }
    
    std::clog << "\rDone.                 \n";

    //actually generate image
    if (!stbi_write_png("output/A.png", image_w, image_h, comp, img, image_w * comp)) {
        std::cerr << "Unable to create A.png" << '\n';
        return -1;
    }
    return 0;
}
