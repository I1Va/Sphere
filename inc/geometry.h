#ifndef GEOMETRY_H
#define GEOMETRY_H

struct geom_dot3;
struct geom_dot2;
class geom_vector2;
class geom_vector3;


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
public:
    geom_vector3(double x, double y, double z): x(x), y(y), z(z) {};    
};


#endif // GEOMETRY_H