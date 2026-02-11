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
            auto r = double(j)/img_width;
            auto g = double(i)/img_height;
            auto b = double(std::min(i, j))/double(std::max(i, j)+1);

            int ir = int(255.999*r);
            int ig = int(255.999*g);
            int ib = int(255.999*b);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::clog << "\rDone.               \n";
}