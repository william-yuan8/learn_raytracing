#include "vec3.h"
#include "color.h"

#include <iostream>

// Output a simple PPM image

int main() {
    // Specify image width and height
    int img_width = 1000;
    int img_height = 1000;

    // Render
    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n"; 

    // Pixels
    for (int i=0; i<img_height; i++) {
        std::clog << "\rRows remaining: " << (img_height-i) << " " << std::flush;
        for (int j=0; j<img_width; j++) {
            auto pix_col = color(double(j)/img_width, 
                                double(i)/img_height,
                                double(std::min(i, j))/double(std::max(i, j)+1));
            write_color(std::cout, pix_col);
        }
    }

    std::clog << "\rDone.               \n";
}