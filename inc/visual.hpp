#ifndef VISUAL_HPP
#define VISUAL_HPP

#include <SFML/Graphics.hpp>

#include "geometry.hpp"

struct pixel_color;
struct pixel_bufer;
struct pixel_dot;

std::ostream& operator<<(std::ostream& stream, const pixel_color color);
void draw_pixel(pixel_bufer &pixel_bufer, pixel_dot pixel, pixel_color color);
geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset);


struct pixel_color {
    int r, g, b;
    pixel_color(int r, int g, int b): r(r), g(g), b(b) {};
    sf::Color to_sfml_color() {return sf::Color(r, g, b);}
   
};

struct pixel_bufer {
    int width;
    int height;
    std::vector<sf::Vertex> data;
    pixel_bufer(int width, int height): width(width), height(height), data(width * height) {};
};

struct pixel_dot {
    int x, y;
    pixel_dot(int x, int y): x(x), y(y) {}
    sf::Vector2f to_sfml_vec2() { return sf::Vector2f(x, y); }
    pixel_dot operator-(const pixel_dot other) { return pixel_dot(x - other.x, y - other.y); }
    int get_radius2() { return x * x + y * y; }
};

struct visual_parameters {
    double pixel_scale;
    pixel_dot pixel_cordsys_offset;
    pixel_color outsphere_color;
    double ambient_intensity;
    geom_dot3 light_src_center;
    double light_src_intensity;
};

class light_source {
    geom_dot3 center;
    double intensity;
    light_source(geom_dot3 center, double intensity): center(center), intensity(intensity) {};
};


#endif // VISUAL_HPP