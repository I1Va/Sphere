#include "geometry.hpp"
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <cassert>


// geom_dot2
geom_dot2::geom_dot2(const double x, const double y): x(x), y(y) { radius2 = x * x + y * y; }
    
double geom_dot2::get_x() const { return x; }
double geom_dot2::get_y() const { return y; }
double geom_dot2::get_radius2() const { return radius2; }

geom_dot2 geom_dot2::operator-(const geom_dot2 &other) const {
    return geom_dot2(x - other.x, y - other.y);
}


// geom_dot3
geom_dot3::geom_dot3(const geom_vector3 &src): x(src.get_x()), y(src.get_y()), z(src.get_z()) {}
geom_dot3::geom_dot3(const double x, const double y, const double z): x(x), y(y), z(z) {};
geom_dot2 geom_dot3::get_xy_dot() const { return geom_dot2(x, y); }
double geom_dot3::get_x() const { return x; }
double geom_dot3::get_y() const { return y; }
double geom_dot3::get_z() const { return z; }
double geom_dot3::get_xy_radius_len() const { return std::sqrt(x * x + y * y); }

std::ostream& operator<<(std::ostream& stream, const geom_dot3 &dot) {
    stream << "geom_dot3 {" << dot.x << ", " << dot.y << ", " << dot.z << "}\n";
    return stream;
}


// geom_vector2
geom_vector2::geom_vector2(const double x, const double y): x(x), y(y) {}; 


// geom_vector3
geom_vector3::geom_vector3(const double x, const double y, const double z): x(x), y(y), z(z), len2(NAN) {};    
geom_vector3::geom_vector3(const geom_dot3 &dot): x(dot.get_x()), y(dot.get_y()), z(dot.get_z()), len2(NAN) {};
geom_vector3::geom_vector3(const double val): x(val), y(val), z(val), len2(NAN) {};

double geom_vector3::get_x() const { return x; };
double geom_vector3::get_y() const { return y; };
double geom_vector3::get_z() const { return z; };
double geom_vector3::get_len2() {
    if (std::isnan(len2))
        len2 = x * x + y * y + z * z;

    return len2;
};

geom_vector3 geom_vector3::operator-(const geom_vector3 &other) {
    len2 = NAN;
    return geom_vector3(x - other.x, y - other.y, z - other.z);
}

geom_vector3 geom_vector3::operator*(const geom_vector3& other) {
    len2 = NAN;
    return geom_vector3(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
}

geom_vector3 geom_vector3::operator*(const double scalar) {
    if (len2 != NAN) len2 *= scalar * scalar;

    return geom_vector3(x * scalar, y * scalar, z * scalar);
}

geom_vector3 geom_vector3::operator+(const geom_vector3 &other) {
    len2 = NAN;
    return geom_vector3(x + other.x, y + other.y, z + other.z);
}

geom_vector3 geom_vector3::operator!() {
    double len = std::sqrt(get_len2());
    len2 = NAN;

    return geom_vector3(x / len, y / len, z / len);
}

geom_vector3 geom_vector3::operator+=(const geom_vector3 &other) {
    len2 = NAN;
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

double geom_vector3::operator^(const geom_vector3& other) {
    len2 = NAN;
    return x * other.x + y * other.y + z * other.z;
}

geom_vector3 geom_vector3::clamp(const double min, const double max) {
    len2 = NAN;
    return geom_vector3
    (
        std::clamp(x, min, max),
        std::clamp(y, min, max),
        std::clamp(z, min, max)
    );
}

std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector) {
    stream << "geom_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

geom_vector3 cord_mul(const geom_vector3 &a, const geom_vector3 &b) {
    return geom_vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

geom_vector3 cord_pow(const geom_vector3 &a, const double pow_val) {
    return geom_vector3
    (
        std::pow(a.x, pow_val),
        std::pow(a.y, pow_val),
        std::pow(a.z, pow_val)
    );
}


// geom_sphere2
geom_sphere2::geom_sphere2(const geom_dot2 &center, const double radius): center(center), radius(radius) {}


// geom_sphere3
geom_sphere3::geom_sphere3(const geom_dot3 &center, const double radius): center(center), radius(radius) {}

geom_dot3 geom_sphere3::place_dot2_on_sphere(const geom_dot2 &dot) {
    assert(is_dot_on_sphere2(dot, geom_dot2(center.get_x(), center.get_y()), radius));

    geom_dot2 delta_dot = dot - center.get_xy_dot();

    return geom_dot3(delta_dot.get_x(), delta_dot.get_y(), std::sqrt(radius * radius - delta_dot.get_radius2()));
}

// general functions:
geom_vector3 get_ortogonal(geom_vector3 &a, geom_vector3 &b) {
    double b_len = std::sqrt(b.get_len2());
    double c = (a ^ b) / (b_len * b_len);
    return a - b * c;
}

bool is_dot_on_sphere2(const geom_dot2 &dot, const geom_dot2 &center, const double radius) {
    double dx = dot.x - center.x;
    double dy = dot.y - center.y;

    return (dx * dx + dy * dy <= radius * radius);
}
