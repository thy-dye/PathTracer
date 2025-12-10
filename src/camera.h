#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "hittable.h"
#include "material.h"
#include "ray.h"

class camera {
    public:
        double aspect_ratio     = 1.0;    //ratio of width over height
        int image_w             = 100;    //image width
        int samples_per_pixel   = 10;     //random samples for each pixel
        int max_depth           = 10;     //Maximum of ray bounces in the scene

        //camera specificiations
        double vfov             = 90;           // Vertical view angle
        vec3 lookfrom           = vec3(0,0,0);  // Point to look from
        vec3 lookat             = vec3(0,0,-1); // Point to look at
        vec3 vup                = vec3(0,1,0);  // Camera-space up

        double defocus_angle = 0; //variation of angle rays through each pixel
        double focus_dist = 10; //distance from lookfrom point to plane of perfect focus

        uint8_t* render(const hittable& world) {
            initialize();

            std::cout << "Image Dimensions: " << image_w << " " << image_h << "\n";

            for (int j = 0;  j < image_h; j++) {
                std::clog << "\rScanlines remaining: " << (image_h - j) << std::flush;
                for (int i = 0; i < image_w; i++) {
                    color3 pixel_color = color3(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(img.data(), comp, pixel_index, pixel_samples_scale * pixel_color);
                    pixel_index++;
                }
            }
            
            std::clog << "\rDone.                   \n";
            
            return img.data();
        }

        //getter methods
        const uint8_t* get_img() const { return img.data(); }
        const int& get_width()   const { return image_w; }
        const int& get_height()  const { return image_h; }
        const int& get_comp()    const { return comp; }
        
        private:
        int image_h;                    //image height
        std::vector<uint8_t> img;       // actual image
        int pixel_index = 0;            //index for the current pixel
        const int comp = 4;             //number of components in the image
        double pixel_samples_scale;     //color scale factor
        point3 origin;                  //camera origin
        point3 pixel00_loc;             //location of pixel 0, 0
        vec3 pixel_delta_u;             //offset to right 
        vec3 pixel_delta_v;             //offset to the left
        vec3 u,v,w;                     //camera space basis vectors
        vec3 defocus_disc_u;            //Defocus disk horizontal radius
        vec3 defocus_disc_v;            //Defocus disk vertical radius
        
        void initialize() {
            //calculate height
            image_h = (int(image_w / aspect_ratio) < 1) ? 1 : int(image_w / aspect_ratio);
            
            //allocate the image memory
            img.resize(image_w * image_h * comp);
            
            pixel_samples_scale = 1.0 / samples_per_pixel;
            origin = lookfrom;
            
            //camera & viewport
            double theta = degrees_to_radians(vfov);
            double h = std::tan(theta/2);
            double viewport_h = 2.0 * h * focus_dist;
            double viewport_w = viewport_h * (double(image_w)/image_h);
            
            // Calculate u,v,w basis for camera space
            w = unit_vector(lookfrom - lookat); 
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            
            // Vectors that span the entire viewport
            vec3 viewport_u = viewport_w * u;       // Vector across viewport horizontal edge
            vec3 viewport_v = viewport_h * -v;      // Vector down viewport vertical edge
            
            //delta for each pixel
            pixel_delta_u = viewport_u / image_w;
            pixel_delta_v = viewport_v / image_h;
            
            //vector of pixel 00's center
            vec3 viewport_upper_left = origin - (focus_dist * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
            
            //calculate camera defocus disk vector space - basis vectors
            double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disc_u = u * defocus_radius;
            defocus_disc_v = v * defocus_radius; 
        }
        
        color3 ray_color(const ray& r, int depth, const hittable& world) {
            if (depth <= 0) {
                return color3(0,0,0);
            }
            
            hit_record rec;
            
            //check if any hittable was hit
            if (world.hit(r, interval(0.001, infinity), rec)) { //0.001 is needed to get rid of shadow acne
                ray scattered;
                color3 attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                    return attenuation * ray_color(scattered, depth-1, world);
                }
                return color3(0, 0, 0);
            }
            
            //background is a vertical lerp from blue to white
            vec3 unit_direction = unit_vector(r.direction());
            double a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color3(1.0, 1.0, 1.0) + a*color3(0.5, 0.7, 1.0);
        }
        
        //gets a ray at a position from the defocus lens to a position around the designated coordinates
        ray get_ray (double u, double v) { 
            vec3 sample_offset = sample_square();
            vec3 pixel_sample = pixel00_loc 
            + (u + sample_offset.x()) * pixel_delta_u 
            + (v + sample_offset.y()) * pixel_delta_v;
            
            vec3 ray_origin = (defocus_angle < 0) ? origin : defocus_disk_sample();
            vec3 ray_direction =  pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction); 
        }
        
        vec3 sample_square () const {
            //return random vector in [-0.5, -0.5] to [0.5, 0.5] square
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }
        
        point3 defocus_disk_sample() {
            //random point on cameras defocus disk
            vec3 p = random_in_unit_disc();
            return origin + (p[0] * defocus_disc_u) + (p[1] * defocus_disc_v); 
        }
    };
    
#endif