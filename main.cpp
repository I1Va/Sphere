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
    .pixel_scale = 1.0 / 200,
    .pixel_cordsys_offset = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
    .outsphere_color = pixel_color(32, 32, 32),
    .ambient_intensity = 0.2,
    .light_src_center = geom_dot3(10, 0, 10),
    .light_src_intensity = geom_vector3(0.8, 0.7, 0.6),
    .sphere_color = pixel_color(32, 120, 64),
    .view_center = geom_dot3(0, 0, 5),
    .view_light_pow = 10
};


int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Sphere");
    pixel_bufer window_pixel_bufer(WINDOW_WIDTH, WINDOW_HEIGHT);


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
    
        static const double trajectory_radius = main_pars.light_src_center.get_xy_radius_len();
        update_light_src_position(&main_pars.light_src_center, ANIMATION_SPEED, trajectory_radius);

        fill_vertex_bufer(window_pixel_bufer, &main_pars);
        window.draw(window_pixel_bufer.data.data(), window_pixel_bufer.data.size(), sf::PrimitiveType::Points);

        window.display();
    }
}