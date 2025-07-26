#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

class hittable_list : public hittable {
    public:
        //members
        std::vector<shared_ptr<hittable>> objects;

        //constructors
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        //clear list
        void clear() { objects.clear(); }

        //add object to end of list
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        //hit detection
        bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            double closest_so_far = ray_t.max;

            for (const shared_ptr<hittable> &object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }
};

#endif