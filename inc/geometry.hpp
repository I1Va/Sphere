#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cmath>
#include <iostream>


struct geom_dot3;
struct geom_dot2;
class geom_vector2;
class geom_vector3;
struct geom_sphere2;
struct geom_sphere3;


geom_vector3 get_ortogonal(const geom_vector3 &a, const geom_vector3 &b);
bool is_dot_on_sphere2(const geom_dot2 &dot, const geom_dot2 &center, const double radius);


class geom_dot2 {
    double x, y;
    double radius2;
public:
    geom_dot2(const double x, const double y);
    
    double get_x() const;
    double get_y() const;
    double get_radius2() const;

    geom_dot2 operator-(const geom_dot2 &other) const;
    
    friend bool is_dot_on_sphere2(const geom_dot2 &dot, const geom_dot2 &center, const double radius);
};

class geom_dot3 {
    double x, y, z;
public:
    geom_dot3(const double x, const double y, const double z);
    explicit geom_dot3(const geom_vector3 &src);

    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_xy_radius_len() const;
    geom_dot2 get_xy_dot() const;
    
    friend std::ostream &operator<<(std::ostream &stream, const geom_dot3 &dot);
};

class geom_vector2 {
    double x, y;
public:
    geom_vector2(const double x, const double y);    
};

class geom_vector3 {
    double x, y, z;
    double len;
public:
    geom_vector3(const double x, const double y, const double z);
    explicit geom_vector3(const geom_dot3 &dot);
    explicit geom_vector3(const double val);
    
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_len() const;

    geom_vector3 operator-(const geom_vector3 &other) const;
    geom_vector3 operator!() const;
    geom_vector3 operator+(const geom_vector3 &other) const;
    geom_vector3 operator+=(const geom_vector3 &other);
    double       operator^(const geom_vector3 &other) const;
    geom_vector3 operator*(const geom_vector3 &other) const;
    geom_vector3 operator*(const double scalar) const;
    
    geom_vector3 clamp(const double min, const double max) const;
    friend std::ostream &operator<<(std::ostream &stream, const geom_vector3 &vector);
    friend geom_vector3 cord_mul(const geom_vector3 &a, const geom_vector3 &b);
    friend geom_vector3 cord_pow(const geom_vector3 &a, const double pow_val);
};

class geom_sphere2 {
    geom_dot2 center;
    double radius;
public:
    geom_sphere2(const geom_dot2 &center, const double radius);
};

class geom_sphere3 {
    geom_dot3 center;
    double radius;
public:
    geom_sphere3(const geom_dot3 &center, const double radius);

    geom_dot3 place_dot2_on_sphere(const geom_dot2 &dot);
};


#endif // GEOMETRY_HPP