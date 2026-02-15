#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {
    public:
        // Aspect ratio and image dimensions
        double aspect_ratio = 16.0/9.0;
        int image_width = 800;
        int samples_per_pixel = 100;
        int max_depth = 10;
    
        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n"; 

            for (int i=0; i<image_height; i++) {
                std::clog << "\rRows remaining: " << (image_height-i) << " " << std::flush;
                for (int j=0; j<image_width; j++) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(j, i);
                        pixel_color += ray_color(r, world, max_depth);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
            }

            std::clog << "\rDone.               \n";
        }

    private:
        int image_height;
        double pixel_samples_scale;
        point3 center;
        point3 pixel00_loc;
        point3 pixel_du;
        point3 pixel_dv;

        void initialize() {
            image_height = int(image_width/aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 0);

            pixel_samples_scale = 1.0/samples_per_pixel;

            // Camera
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Viewport vectors
            auto vp_u = vec3(viewport_width, 0, 0);
            auto vp_v = vec3(0, -viewport_height, 0);

            // Ratio of viewport size per pixel
            pixel_du = vp_u/image_width;
            pixel_dv = vp_v/image_height;

            // Upper left pixel location
            auto vp_ul = center - vp_u/2 - vp_v/2 - vec3(0, 0, focal_length);
            pixel00_loc = vp_ul + 0.5 * (pixel_du + pixel_dv);
        }
        
        color ray_color(const ray& r, const hittable& world, int depth) const {
            hit_record rec;
            if (depth <= 0) {
                return color(0, 0, 0);  
            }

            if (world.hit(r, interval(2e-5, infinity), rec)) {
                ray scattered;
                color atten;
                if (rec.mat->scatter(r, rec, atten, scattered)) {
                    return atten * ray_color(scattered, world, depth-1);
                }
                return color(0, 0, 0);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }

        ray get_ray(int i, int j) const {

            auto offset = sample_square();
            auto sample_loc = pixel00_loc + ((i + offset.x()) * pixel_du) + ((j + offset.y()) * pixel_dv);

            return ray(center, sample_loc - center);
        }   

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }
};

#endif