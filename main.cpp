#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>

#include "geometry.hpp"
#include "visual.hpp"
#include "calculations.hpp"


static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const double ANIMATION_SPEED = 0.01;

visual_parameters main_pars
{   
    
    .outsphere_color = {32, 32, 32},
    

    .sphere_color       = geom_vector3(0.1, 0.8, 0.2),
    .ambient_intensity  = geom_vector3(0.2, 0.2, 0.2),
    .defuse_intensity   = geom_vector3(0.8, 0.7, 0.6),
    .specular_intensity = geom_vector3(0.7, 0.7, 0),
    
    .light_src_center = geom_dot3(10, 0, 10),
    .view_center      = geom_dot3(0, 0, 5),

    .view_light_pow = 15,   
    .pixel_scale = 1.0 / 200,
    .pixel_cordsys_offset = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
};


// class coord_system {
//     geom_dot3 center;
//     double pixel_scale;
// public:
//     coord_system(const geom_dot3 &center, const double pixel_scale)
// };

// void make_axes(const geom_dot3 ) {

// }



int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Sphere");
    pixel_bufer window_pixel_bufer = {WINDOW_WIDTH, WINDOW_HEIGHT};


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
    
        static const double trajectory_radius = main_pars.light_src_center.get_xy_radius_len();
        update_light_src_position(&main_pars.light_src_center, ANIMATION_SPEED, trajectory_radius);

        fill_pixel_bufer(window_pixel_bufer, &main_pars);
        window.draw(window_pixel_bufer.data(), window_pixel_bufer.size(), sf::PrimitiveType::Points);

        window.display();
    }
}
