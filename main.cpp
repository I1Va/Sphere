#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>

#include "geometry.hpp"
#include "visual.hpp"
#include "calculations.hpp"


static const int window_width = 640;
static const int window_height = 480u;

const visual_parameters main_pars
{
    .pixel_scale = 1.0 / 200,
    .pixel_cordsys_offset = {window_width / 2, window_height / 2},
    .sphere_center = geom_dot3(0, 0, 0),
    .outsphere_color = pixel_color(32, 32, 32),
    .sphere_radius = 1
};


int main()
{
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "Sphere");
    pixel_bufer window_pixel_bufer(window_width, window_height);

    fill_vertex_bufer(window_pixel_bufer, &main_pars);

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