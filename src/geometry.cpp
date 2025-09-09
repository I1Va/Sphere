#include "geometry.hpp"
#include <cfloat>
#include <cmath>

geom_vector3 geom_vector3::operator-(const geom_vector3 &other) const {
    return geom_vector3(x - other.x, y - other.y, z - other.z);
}

geom_vector3 geom_vector3::operator+(const geom_vector3 &other) const {
    return geom_vector3(x + other.x, y + other.y, z + other.z);
}

geom_vector3 geom_vector3::operator!() const {
    return geom_vector3(x / len, y / len, z / len);
}

double geom_vector3::operator^(const geom_vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

geom_dot3::geom_dot3(const geom_vector3 &src): x(src.get_x()), y(src.get_y()), z(src.get_z()) {}

geom_vector3 geom_vector3::operator+=(const geom_vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    len = std::sqrt(x * x + y * y + z * z);
    return *this;
}

geom_vector3 geom_vector3::operator*(const geom_vector3& other) const {
    return geom_vector3(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
}

geom_vector3 geom_vector3::operator*(const double scalar) const {
    return geom_vector3(x * scalar, y * scalar, z * scalar);
}

geom_vector3 get_ortogonal(const geom_vector3 &a, const geom_vector3 &b) {
    double b_len = b.get_len();
    double c = (a ^ b) / (b_len * b_len);
    return a - b * c;
}

std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector) {
    stream << "geom_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const geom_dot3 &dot) {
    stream << "geom_dot3 {" << dot.x << ", " << dot.y << ", " << dot.z << "}\n";
    return stream;
}

