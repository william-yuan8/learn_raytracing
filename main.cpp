#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

bool hit_sphere(const point3& center, double rad, const ray& r) {
    // if the discriminant of the formula is negative, no intersection, return false
    // otherwise return true
    double a = r.direction().length_squared();
    double b = dot(-2*r.direction(), center-r.origin());
    double c = dot(center-r.origin(), center-r.origin()) - rad*rad;

    return b*b >= 4*a*c;
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(-1, -1, -2), 0.5, r)) {
        return color(1, 0, 0);
    }

    if (hit_sphere(point3(1, 1, -1), 0.3, r)) {
        return color(0, 1, 0);
    }

    if (hit_sphere(point3(-1, 2, -5), 1, r)) {
        return color(0, 0, 1);
    }
    
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y()+1.0);
    return (1.0-a)*color(1, 1, 1) + a*color(0.071, 0.89, 0.922);
}

int main() {
    // Aspect ratio and image dimensions
    auto aspect_ratio = 16.0/9.0;
    int image_width = 800;

    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Viewport vectors
    auto vp_u = vec3(viewport_width, 0, 0);
    auto vp_v = vec3(0, -viewport_height, 0);

    // Ratio of viewport size per pixel
    auto pixel_du = vp_u/image_width;
    auto pixel_dv = vp_v/image_height;

    // Upper left pixel location
    auto vp_ul = camera_center - vp_u/2 - vp_v/2 - vec3(0, 0, focal_length);
    auto pixel00_loc = vp_ul + 0.5 * (pixel_du + pixel_dv);

    // Specify image width and height

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n"; 

    // Pixels
    for (int i=0; i<image_height; i++) {
        std::clog << "\rRows remaining: " << (image_height-i) << " " << std::flush;
        for (int j=0; j<image_width; j++) {
            auto pixel_center = pixel00_loc + (i*pixel_dv) + (j*pixel_du);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.               \n";
}