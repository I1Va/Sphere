#include "geometry.hpp"


geom_vector3 geom_vector3::operator-(const geom_vector3 &other) {
    return geom_vector3(x - other.x, y - other.y, z - other.z);
}

geom_vector3 geom_vector3::operator!() {
    return geom_vector3(x / len, y / len, z / len);
}

double geom_vector3::operator^(const geom_vector3& other) {
    return x * other.x + y * other.y + z + other.z;
}

std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector) {
    stream << "geom_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}
