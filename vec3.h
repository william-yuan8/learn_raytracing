#ifndef VEC3_H
#define VEC3_H

class vec3 {
    public:
        double e[3];

        vec3() : e{0, 0, 0} {}
        vec3(double e1, double e2, double e3) : e{e1, e2, e3} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        vec3& operator+=(const vec3& v) {
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];
            return *this;
        }

        vec3& operator*=(const vec3& v) {
            e[0] *= v[0];
            e[1] *= v[1];
            e[2] *= v[2];
            return *this;
        }

        vec3& operator/=(const vec3& v) {
            e[0] /= v[0];
            e[1] /= v[1];
            e[2] /= v[2];
            return *this;
        }

        double length() const {return std::sqrt(length_squared());}
        double length_squared() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool near_zero() const {
            const auto s = 1e-8;
            return length_squared() < s*s;
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << " " << v[1] << " " << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u[0]*v[0], u[1]*v[1], u[2]*v[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t*v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1]*v[2]-u[2]*v[1], u[2]*v[0]-u[0]*v[2], u[0]*v[1]-u[1]*v[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v/v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto v = vec3::random(-1, 1);
        auto length_squared = v.length_squared();
        if (length_squared > 1e-160 && length_squared <= 1) return v/sqrt(length_squared);
    }
}

inline vec3 random_face_normal(const vec3& normal) {
    auto v = random_unit_vector();
    if (dot(v, normal) > 0.0)
        return v;
    else
        return -v;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n)*n;
}

#endif