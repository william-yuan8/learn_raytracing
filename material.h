#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& r, const hit_record& rec, color& atten, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray&, const hit_record& rec, color& atten, ray& scattered) const override {
            vec3 scatter_dir = rec.normal + random_unit_vector();
            if (scatter_dir.near_zero()) {
                scatter_dir = rec.normal;
            }
            scattered = ray(rec.p, scatter_dir);
            atten = albedo;
            return true;
        }

    private:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

        bool scatter(const ray& r, const hit_record& rec, color& atten, ray& scattered) const override {
            vec3 reflected = reflect(r.direction(), rec.normal) + (fuzz*random_unit_vector());
            scattered = ray(rec.p, reflected);
            atten = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
    
    private:
        color albedo;
        double fuzz;
};

#endif