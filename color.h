#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pix_col) {
    int r = int(pix_col[0]*255.999);
    int g = int(pix_col[1]*255.999);
    int b = int(pix_col[2]*255.999);

    out << r << " " << g << " " << b << "\n";
}

#endif