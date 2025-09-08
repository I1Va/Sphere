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

bool is_dot_on_sphere2(geom_dot2 dot, geom_dot2 center, double radius);
bool is_dot_on_sphere2(geom_dot2 dot, geom_dot2 center, double radius);


struct geom_dot3 {
    double x, y, z;
    geom_dot3(double x, double y, double z): x(x), y(y), z(z) {};  
};

struct geom_dot2 {
    double x, y;
    geom_dot2(double x, double y): x(x), y(y) {};  
};

class geom_vector2 {
    double x, y;
public:
    geom_vector2(double x, double y): x(x), y(y) {};    
};

class geom_vector3 {
    double x, y, z;
    double len;
public:
    geom_vector3(double x, double y, double z): x(x), y(y), z(z) { len = std::sqrt(x * x + y * y + z * z); };    
    geom_vector3(geom_dot3 dot): x(dot.x), y(dot.y), z(dot.z) {}; 

    double get_len() { return len; };
    geom_vector3 operator-(const geom_vector3& other);
    geom_vector3 operator!();
    double operator^(const geom_vector3& other);

    friend std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector);
};

struct geom_sphere2 {
    geom_dot2 center;
    double radius;
    geom_sphere2(geom_dot2 center, double radius): center(center), radius(radius) {}
    bool contain_dot(geom_dot2 dot) { return dot.x * dot.x + dot.y + dot.y <= radius * radius; }
};

struct geom_sphere3 {
    geom_dot3 center;
    double radius;
    geom_sphere3(geom_dot3 center, double radius): center(center), radius(radius) {}
    geom_dot3 place_dot2_on_sphere(geom_dot2 dot);
};


#endif // GEOMETRY_HPP