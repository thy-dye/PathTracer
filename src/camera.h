#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_w = 100;

        uint8_t* render(const hittable& world) {
            initialize();

            std::cout << "Image Dimensions: " << image_w << " " << image_h << "\n";

            for (int j = 0;  j < image_h; j++)
            {
                std::clog << "Scanlines remaining: " << (image_h - j) << " \n" << std::flush;

                for (int i = 0; i < image_w; i++) 
                {
                    point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    vec3 ray_direction = pixel_center - center;

                    ray r = ray(center, ray_direction);

                    color3 pixel_color = ray_color(r, world);
                    
                    write_color(img.data(), comp, pixel_index, pixel_color);
                    pixel_index++;
                }
            }
            
            std::clog << "\rDone.                 \n";

            return img.data();
        }

        const uint8_t* get_img() const {
            return img.data();
        }

        const int& get_width() const {
            return image_w;
        }

        
        const int& get_height() const {
            return image_h;
        }

        const int& get_comp() const {
            return comp;
        }

    private:
        std::vector<uint8_t> img;
        int pixel_index = 0;
        const int comp = 4;
        int image_h;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            //calculate height
            image_h = (int(image_w / aspect_ratio) < 1) ? 1 : int(image_w / aspect_ratio);

            //allocate the image memory
            img.resize(image_w * image_h * comp);
            
            center = point3(0, 0, 0);

            //camera & viewport
            double focal_length = 1.0;
            double viewport_h = 2.0;
            double viewport_w = viewport_h * (double(image_w)/image_h);

            // Vectors that span the entire viewport
            vec3 viewport_u = vec3(viewport_w, 0, 0);
            vec3 viewport_v = vec3(0, -viewport_h, 0);

            //delta for each pixel
            pixel_delta_u = viewport_u / image_w;
            pixel_delta_v = viewport_v / image_h;

            //vector of pixel 00's center
            vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }

        color3 ray_color(const ray& r, const hittable& world) {
            hit_record rec;

            //check if any hittable was hit
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color3(1, 1, 1));
            }

            //background is a vertical lerp from blue to white
            vec3 unit_direction = unit_vector(r.direction());
            double a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color3(1.0, 1.0, 1.0) + a*color3(0.5, 0.7, 1.0);
        }
};

#endif