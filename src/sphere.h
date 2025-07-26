#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public: 
        sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0,radius)) {}

        //hit detection for sphere
        bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
            //quadratic formula variables a h and c where -2h = b
            vec3 oc = center - r.origin();
            double a = r.direction().squared_length();
            double h = dot(r.direction(), oc);
            double c = oc.squared_length() - radius*radius;
            double discriminant = h*h - a*c;

            //how many solutions -> hits
            if (discriminant < 0) {
                return false;
            } 

            double sqrtd = std::sqrt(discriminant);

            //checks if closer/outer vector is in range
            double root = (h - sqrtd) / a;
            if (root <= ray_t.min || ray_t.max <= root) {
                root = (h + sqrtd) / a;
                if (root <= ray_t.min || ray_t.max <= root) {
                    return false;
                }
            }

            //hit record information
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

    private: 
        point3 center;
        double radius;
};

#endif