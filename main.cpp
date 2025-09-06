#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>
#include "geometry.h"

const int window_width = 640;
const int window_height = 480u;

struct pixel_color {
    int r, g, b;
    pixel_color(int r, int g, int b): r(r), g(g), b(b) {};
    sf::Color to_sfml_color() {return sf::Color(r, g, b);}
   
};

std::ostream& operator<<(std::ostream& stream, const pixel_color color) {
    stream << "{RGB: " << color.r << " " << color.g << " " << color.b << "}\n";
    return stream;
}

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




void draw_pixel(pixel_bufer &pixel_bufer, pixel_dot pixel, pixel_color color) {
    pixel_bufer.data[pixel.y * pixel_bufer.width + pixel.x] = {pixel.to_sfml_vec2(), color.to_sfml_color()};
}




geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset) {
    pixel_dot pixel_with_offset = pixel_dot(pixel.x, pixel.y) - pixel_cordsys_offset;
    geom_dot2 geom_dot((double)(pixel_with_offset.x) * pixel_scale, (double) (pixel_with_offset.y) * pixel_scale);

    return geom_dot;
}

struct geom_sphere2 {
    geom_dot2 center;
    double radius;
    geom_sphere2(geom_dot2 center, double radius): center(center), radius(radius) {}
    bool contain_dot(geom_dot2 dot) { return dot.x * dot.x + dot.y + dot.y <= radius * radius; }
};


bool is_dot_on_sphere2(geom_dot2 dot, geom_dot2 center, double radius) {
    double dx = dot.x - center.x;
    double dy = dot.y - center.y;

    return (dx * dx + dy * dy <= radius * radius);
}

struct geom_sphere3 {
    geom_dot3 center;
    double radius;
    geom_sphere3(geom_dot3 center, double radius): center(center), radius(radius) {}
    geom_dot3 place_dot2_on_sphere(geom_dot2 dot) {
        assert(is_dot_on_sphere2(dot, geom_dot2(center.x, center.y), radius));
        
        double dx2 = (dot.x - center.x) * (dot.x - center.x);
        double dy2 = (dot.y - center.y) * (dot.y - center.y);

        return geom_dot3(dot.x, dot.y, std::sqrt(radius * radius - dx2 - dy2));
    }
};


static const pixel_dot PIXEL_SPHERE_CENTER = {window_width / 2, window_height / 2};
static const pixel_color OUT_SPHERE_COLOR = {32, 32, 32};
// static const pixel_color COLOR_RED = {255, 0, 0};
static const double PIXEL_SCALE = 1.0 / 200;

static const double GEOM_SPHERE_RADIUS = 1;
static const geom_dot2 GEOM2_SPHERE_CENTER = geom_dot2(0, 0);
static const geom_dot3 GEOM3_SPHERE_CENTER = geom_dot3(0, 0, 0);

















int main()
{
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "Sphere");
    pixel_bufer window_pixel_bufer(window_width, window_height);

    for (int pixel_x = 0; pixel_x < window_width; pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_height; pixel_y++) {
            pixel_dot cur_pixel = {pixel_x, pixel_y};
            geom_dot2 dot2 = convert_pixel_to_geom_dot2(cur_pixel, PIXEL_SCALE, PIXEL_SPHERE_CENTER);

            if (!is_dot_on_sphere2(dot2, GEOM2_SPHERE_CENTER, GEOM_SPHERE_RADIUS)) {
                draw_pixel(window_pixel_bufer, cur_pixel, OUT_SPHERE_COLOR);
                continue;
            }

            geom_sphere3 sphere3(GEOM3_SPHERE_CENTER, GEOM_SPHERE_RADIUS);
            geom_dot3 sphere_dot = sphere3.place_dot2_on_sphere(dot2);

            pixel_color color = {32 + sphere_dot.z * 100, 32 + sphere_dot.z * 100, 32 + sphere_dot.z * 100};
            draw_pixel(window_pixel_bufer, cur_pixel, color);
            
        }
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(window_pixel_bufer.data.data(), window_pixel_bufer.data.size(), sf::PrimitiveType::Points);
        window.display();
    }
}