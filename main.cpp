#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

const int window_width = 640;
const int window_height = 480u;
const int pixel_center_x = window_width / 2;
const int pixel_center_y = window_height / 2;


struct pixel_dot {
    int x, y;
    pixel_dot(int x, int y): x(x), y(y) {}
    sf::Vector2f to_sfml_vec2() {return sf::Vector2f(x, y);}
    pixel_dot operator-=(const pixel_dot other) { return pixel_dot(x - other.x, y - other.y); }
};

struct pixel_color {
    int r, g, b;
public:
    pixel_color(int r, int g, int b): r(r), g(g), b(b) {};
    sf::Color to_sfml_color() {return sf::Color(r, g, b);}

};

struct geom_dot {
    double x, y, z;
    geom_dot(double x, double y, double z): x(x), y(y), z(z) {};  
};

class geom_vector {
    double x, y, z;
public:
    geom_vector(double x, double y, double z): x(x), y(y), z(z) {};    
};

struct pixel_bufer {
    int width;
    int height;
    std::vector<sf::Vertex> data;
    pixel_bufer(int width, int height): width(width), height(height), data(width * height) {};
};

geom_dot get_cordsys3_dot(pixel_dot dot, pixel_dot center) {
    dot -= center;

    int dot_x2 = dot.x * dot.x;
    int dot_y2 = dot.y * dot.y;

    double dot_radius2 = dot.x * dot.x + dot.y * dot.y;
    double z = std::sqrt(dot_radius2 - dot_x2 - dot_y2);

    return geom_dot(dot.x, dot.y, z);
}


bool is_pixel_in_sphere(const pixel_dot center, const int radius, const pixel_dot src_dot) {
    int dx = abs(src_dot.x - center.x);
    int dy = abs(src_dot.y - center.y);

    return (dx * dx + dy * dy <= radius * radius);
}

const pixel_dot PIXEL_SPHERE_CENTER = {window_width / 2, window_height / 2};
const int PIXEL_SPHERE_RADIUS = 200;
const pixel_color OUT_SPHERE_COLOR = {32, 32, 32};
const pixel_color COLOR_RED = {255, 0, 0};

void draw_pixel(pixel_bufer &pixel_bufer, pixel_dot pixel, pixel_color color) {
    pixel_bufer.data[pixel.y * pixel_bufer.width + pixel.x] = {pixel.to_sfml_vec2(), color.to_sfml_color()};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "My window");
    pixel_bufer window_pixel_bufer(window_width, window_height);

    (window_width * window_height);

    for (int pixel_x = 0; pixel_x < window_width; pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_height; pixel_y++) {
            pixel_dot cur_pixel = {pixel_x, pixel_y};
            if (!is_pixel_in_sphere(PIXEL_SPHERE_CENTER, PIXEL_SPHERE_RADIUS, cur_pixel)) {
                draw_pixel(window_pixel_bufer, cur_pixel, OUT_SPHERE_COLOR);
                continue;
            }

            geom_dot sph_dot = get_cordsys3_dot(cur_pixel, PIXEL_SPHERE_CENTER);

            pixel_color color = {32 + sph_dot.x, 32 + sph_dot.y, 32 + sph_dot.z};

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