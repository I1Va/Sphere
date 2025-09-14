#include "visual.hpp"
#include <cmath>

const static int COLOR_MAX_VAL = 255;


void draw_pixel(pixel_bufer &pixel_bufer, const gm_vector<int, 2> &pixel, const gm_vector<double, 3> &color_vec) {
    sf::Color color = 
        {   uint8_t(color_vec.get_x() * COLOR_MAX_VAL),
            uint8_t(color_vec.get_y() * COLOR_MAX_VAL), 
            uint8_t(color_vec.get_z() * COLOR_MAX_VAL)
        };
    
    sf::Vector2f pixel_pos(pixel.get_x(), pixel.get_y());
    pixel_bufer[pixel] = {pixel_pos, color};
}

