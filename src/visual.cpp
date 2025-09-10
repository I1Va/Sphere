#include "visual.hpp"
#include <cmath>


// pixel_color
sf::Color pixel_color::to_sfml_color() const { return sf::Color(r, g, b); }


// pixel_dot
pixel_dot::pixel_dot(const int x, const int y): x(x), y(y) { radius2 = x * x + y * y; }

pixel_dot pixel_dot::operator-(const pixel_dot other) const { return pixel_dot(x - other.x, y - other.y); }
sf::Vector2f pixel_dot::to_sfml_vec2() const { return sf::Vector2f(x, y); }
int pixel_dot::get_radius2() const { return radius2; }
int pixel_dot::get_x() const { return x; }
int pixel_dot::get_y() const { return y; }


// pixel_bufer
pixel_bufer::pixel_bufer(int width, int height): width(width), height(height), vector_data(width * height) {};
sf::Vertex& pixel_bufer::operator[](const pixel_dot &dot) {
    return vector_data[dot.get_y() * width + dot.get_x()];
}

size_t pixel_bufer::size() const { return vector_data.size(); }
const sf::Vertex *pixel_bufer::data() const { return vector_data.data(); }

// general functions
std::ostream& operator<<(std::ostream& stream, const pixel_color color) {
    stream << "{RGB: " << color.r << " " << color.g << " " << color.b << "}\n";
    return stream;
}

void draw_pixel(pixel_bufer &pixel_bufer, const pixel_dot &pixel, const pixel_color &color) {
    pixel_bufer[pixel] = {pixel.to_sfml_vec2(), color.to_sfml_color()};
}

void draw_pixel(pixel_bufer &pixel_bufer, const pixel_dot &pixel, const geom_vector3 &color_vec) {
    pixel_color color = {int(color_vec.get_x()), int(color_vec.get_y()), int(color_vec.get_z())};
    pixel_bufer[pixel] = {pixel.to_sfml_vec2(), color.to_sfml_color()};
}

geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset) {
    pixel_dot pixel_with_offset = pixel_dot(pixel.x, pixel.y) - pixel_cordsys_offset;
    geom_dot2 geom_dot((double)(pixel_with_offset.x) * pixel_scale, (double) (pixel_with_offset.y) * pixel_scale);

    return geom_dot;
}
