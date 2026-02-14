#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pix_col) {
    static const interval color_interval(0.0, 0.999);

    int r = int(color_interval.clamp(pix_col[0])*255.999);
    int g = int(color_interval.clamp(pix_col[1])*255.999);
    int b = int(color_interval.clamp(pix_col[2])*255.999);

    out << r << " " << g << " " << b << "\n";
}

#endif