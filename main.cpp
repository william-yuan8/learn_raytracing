#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

double mx=-100000, mn=10000000;

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    mx = std::max(mx, unit_direction.y());
    mn = std::min(mn, unit_direction.y());
    auto a = 0.5*(unit_direction.y()+1.0);
    return (1.0-a)*color(1, 1, 1) + a*color(0, 0, 0);
}

// Output a simple PPM image

int main() {
    // Aspect ratio and image dimensions
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

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
    std::clog << "Image width: " << image_width << " Image height: " << image_height << "\n";
    std::clog << "Camera center: " << camera_center << "\n";
    std::clog << "Pixel00 location: " << pixel00_loc << "\n"; 
    std::clog << "Pixel00 unit vector: " << unit_vector(pixel00_loc) << "\n";
    std::clog << "Pixel_du: " << pixel_du << " Pixel_dv: " << pixel_dv << "\n";
    std::clog << "Max unit y: " << mx << " Min unit y: " << mn << "\n";
}