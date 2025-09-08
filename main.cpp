#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>

#include "geometry.hpp"
#include "visual.hpp"
#include "calculations.hpp"


static const int window_width = 640;
static const int window_height = 480u;

visual_parameters main_pars
{
    .pixel_scale = 1.0 / 200,
    .pixel_cordsys_offset = {window_width / 2, window_height / 2},
    .outsphere_color = pixel_color(32, 32, 32),
    .ambient_intensity = 0.2,
    .light_src_center = geom_dot3(4, 4, 4),
    .light_src_intensity = 0.17,
    .view_center = geom_dot3(3, 3, 3),
    .view_light_pow = 1.0
};


int main()
{
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "Sphere");
    pixel_bufer window_pixel_bufer(window_width, window_height);

    

    while (window.isOpen())
    {
    
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode)
                    {
                    case sf::Keyboard::Scan::Q: main_pars.light_src_center.x += 0.1; break;
                    case sf::Keyboard::Scan::A: main_pars.light_src_center.x -= 0.1; break;

                    case sf::Keyboard::Scan::W: main_pars.light_src_center.y += 0.1; break;
                    case sf::Keyboard::Scan::S: main_pars.light_src_center.y -= 0.1; break;

                    case sf::Keyboard::Scan::E: main_pars.light_src_center.z += 0.1; break;
                    case sf::Keyboard::Scan::D: main_pars.light_src_center.z -= 0.1; break;
                    
                    default:
                        break;
                    }
            }
            std::cout << main_pars.light_src_center << "\n";
        }


        window.clear();

        fill_vertex_bufer(window_pixel_bufer, &main_pars);
        window.draw(window_pixel_bufer.data.data(), window_pixel_bufer.data.size(), sf::PrimitiveType::Points);

        window.display();
    }
}