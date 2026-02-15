#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double to_gamma(double x) {
    if (x > 0)  return std::sqrt(x);

    return 0;
}

void write_color(std::ostream& out, const color& pix_col) {
    static const interval intensity(0, 0.999);

    int r = int(intensity.clamp(to_gamma(pix_col.x()))*256);
    int g = int(intensity.clamp(to_gamma(pix_col.y()))*256);
    int b = int(intensity.clamp(to_gamma(pix_col.z()))*256);

    out << r << " " << g << " " << b << "\n";
}

#endif