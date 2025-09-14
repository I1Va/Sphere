#ifndef VISUAL_HPP
#define VISUAL_HPP

#include <SFML/Graphics.hpp>

#include "gm_primitives.hpp"


class pixel_bufer {
    int width;
    int height;
    std::vector<sf::Vertex> vector_data;
public:
    pixel_bufer(const int width, const int height): width(width), height(height), vector_data(width * height) {}
 
    size_t size() const { return vector_data.size(); }
    int get_width() const { return width; }
    int get_height() const { return height; }
    const sf::Vertex *data() const { return vector_data.data(); };
    
    sf::Vertex& operator[](const gm_vector<int, 2> &pixel) {
        return vector_data[pixel.get_y() * width + pixel.get_x()];
    }

    // friend void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars);
};


struct visual_parameters {
    gm_vector<double, 3> outsphere_color;
    gm_vector<double, 3> sphere_color;

    gm_vector<double, 3> ambient_intensity;
    gm_vector<double, 3> defuse_intensity;
    gm_vector<double, 3> specular_intensity;

    gm_vector<double, 3> light_src_center;
    gm_vector<double, 3> view_center;
    
    double view_light_pow;
    double pixel_scale;
    gm_vector<int, 2> pixel_cordsys_offset;    
};

void draw_pixel(pixel_bufer &pixel_bufer, const gm_vector<int, 2> &pixel, const gm_vector<double, 3> &color_vec);

// struct light_source {
//     geom_dot3 center;
//     double intensity;
// };


#endif // VISUAL_HPP