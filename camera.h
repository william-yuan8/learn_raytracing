#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        // Aspect ratio and image dimensions
        double aspect_ratio = 16.0/9.0;
        int image_width = 800;

    
        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n"; 

            for (int i=0; i<image_height; i++) {
                std::clog << "\rRows remaining: " << (image_height-i) << " " << std::flush;
                for (int j=0; j<image_width; j++) {
                    auto pixel_center = pixel00_loc + (i*pixel_dv) + (j*pixel_du);
                    auto ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }

            std::clog << "\rDone.               \n";
        }

    private:
        int image_height;
        point3 center;
        point3 pixel00_loc;
        point3 pixel_du;
        point3 pixel_dv;

        void initialize() {
            image_height = int(image_width/aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 0);

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
        
        color ray_color(const ray& r, const hittable& world) {
            hit_record rec;
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5*(rec.normal + color(1, 1, 1));
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif