#include "visual.hpp"
#include <cmath>

std::ostream& operator<<(std::ostream& stream, const pixel_color color) {
    stream << "{RGB: " << color.r << " " << color.g << " " << color.b << "}\n";
    return stream;
}

void draw_pixel(pixel_bufer &pixel_bufer, pixel_dot pixel, pixel_color color) {
    pixel_bufer.data[pixel.y * pixel_bufer.width + pixel.x] = {pixel.to_sfml_vec2(), color.to_sfml_color()};
}

geom_dot2 convert_pixel_to_geom_dot2(pixel_dot pixel, double pixel_scale, pixel_dot pixel_cordsys_offset) {
    pixel_dot pixel_with_offset = pixel_dot(pixel.x, pixel.y) - pixel_cordsys_offset;
    geom_dot2 geom_dot((double)(pixel_with_offset.x) * pixel_scale, (double) (pixel_with_offset.y) * pixel_scale);

    return geom_dot;
}

geom_dot3 geom_sphere3::place_dot2_on_sphere(geom_dot2 dot) {
    assert(is_dot_on_sphere2(dot, geom_dot2(center.x, center.y), radius));
    
    double dx2 = (dot.x - center.x) * (dot.x - center.x);
    double dy2 = (dot.y - center.y) * (dot.y - center.y);

    return geom_dot3(dot.x, dot.y, std::sqrt(radius * radius - dx2 - dy2));
}

bool is_dot_on_sphere2(geom_dot2 dot, geom_dot2 center, double radius) {
    double dx = dot.x - center.x;
    double dy = dot.y - center.y;

    return (dx * dx + dy * dy <= radius * radius);
}
