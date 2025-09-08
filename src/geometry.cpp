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
    return x * other.x + y * other.y + z + other.z;
}

geom_vector3 geom_vector3::operator*(const geom_vector3& other) const {
    return geom_vector3(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
};

geom_vector3 geom_vector3::operator*(const double scalar) const {
    return geom_vector3(x * scalar, y * scalar, z * scalar);
};

geom_vector3 rotate_tow_vec(const double radians, const geom_vector3 &rot_vec, const geom_vector3 &anch_ve) {
    geom_vector3 rot_axis = rot_vec * anch_ve;
    if (rot_axis.get_len() < DBL_EPSILON) {
        return geom_vector3(1, 0, 0);
    }
    rot_axis = !rot_axis;

    return rot_vec * std::cos(radians) + (rot_axis * rot_vec) * std::sin(radians) + 
            rot_axis * (rot_axis * rot_vec) * (1 - std::cos(radians));

    
}

std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector) {
    stream << "geom_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const geom_dot3 &dot) {
    stream << "geom_dot3 {" << dot.x << ", " << dot.y << ", " << dot.z << "}\n";
    return stream;
}

