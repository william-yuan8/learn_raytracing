#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double rad, shared_ptr<material> mat) : center(center), rad(std::fmax(0, rad)), mat(mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 co = center-r.origin();
            double a = r.direction().length_squared();
            double h = dot(r.direction(), co);
            double c = dot(co, co) - rad*rad;

            double disc = h*h - a*c;
            if (disc < 0) return false;

            double sqrtd = std::sqrt(disc);

            // nearest root in range tmin < t < tmax
            double root = (h-sqrtd)/a;
            if (!ray_t.surrounds(root)) {
                root = (h+sqrtd)/a;
                if (!ray_t.surrounds(root))
                    return false; 
            }

            rec.mat = mat;
            rec.t = root;
            rec.p = r.at(root);
            vec3 outward_normal = (rec.p - center)/rad;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

    private:
        point3 center;
        double rad;
        shared_ptr<material> mat;
};

#endif