#ifndef VISUAL_HPP
#define VISUAL_HPP

#include <SFML/Graphics.hpp>

#include "geometry.hpp"

struct pixel_color;
struct pixel_bufer;
struct pixel_dot;


struct visual_parameters;
struct light_source;


std::ostream& operator<<(std::ostream& stream, const pixel_color color);
geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset);


class pixel_dot {
    int x, y;
    int radius2;
public:
    pixel_dot(const int x, const int y);

    pixel_dot operator-(const pixel_dot other) const;
    
    sf::Vector2f to_sfml_vec2() const;
    int get_radius2() const;
    int get_x() const; 
    int get_y() const;

    friend void draw_pixel(pixel_bufer &pixel_bufer, const pixel_dot &pixel, const pixel_color &color);
    friend void draw_pixel(pixel_bufer &pixel_bufer, const pixel_dot &pixel, const geom_vector3 &color_vec);
    friend geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset);
};

struct pixel_color {
    int r, g, b;
    sf::Color to_sfml_color() const; 
};

class pixel_bufer {
    int width;
    int height;
    std::vector<sf::Vertex> vector_data;
public:
    size_t size() const;
    const sf::Vertex *data() const;
    pixel_bufer(const int width, const int height);
    sf::Vertex& operator[](const pixel_dot &dot);


    friend void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars);
};

struct visual_parameters {
    double pixel_scale;
    pixel_dot pixel_cordsys_offset;
    pixel_color outsphere_color;
    double ambient_intensity;
    geom_dot3 light_src_center;
    geom_vector3 light_src_intensity;
    pixel_color sphere_color;
    geom_dot3 view_center;
    double view_light_pow;
};

struct light_source {
    geom_dot3 center;
    double intensity;
};


#endif // VISUAL_HPP