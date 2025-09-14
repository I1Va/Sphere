#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>


#include "visual.hpp"
#include "calculations.hpp"
#include "scene.hpp"

#include "gm_primitives.hpp"

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const double ANIMATION_SPEED = 0.01;

visual_parameters main_visual_parameters
{   
    
    .outsphere_color    = gm_vector<double, 3>(0.1, 0.1, 0.1),
    .sphere_color       = gm_vector<double, 3>(0.1, 0.8, 0.2),

    .ambient_intensity  = gm_vector<double, 3>(0.2, 0.2, 0.2),
    .defuse_intensity   = gm_vector<double, 3>(0.8, 0.7, 0.6),
    .specular_intensity = gm_vector<double, 3>(0.7, 0.7, 0),
    
    .light_src_center = gm_vector<double, 3>(10, 0, 10),
    .view_center      = gm_vector<double, 3>(0, 0, 5),

    .view_light_pow = 15,   
    .pixel_scale = 1.0 / 200,
    .pixel_cordsys_offset = gm_vector<int, 2>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
};


int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Sphere");
    pixel_bufer window_pixel_bufer = {WINDOW_WIDTH, WINDOW_HEIGHT};

    scene_manager scene({0, 0, 0}, main_visual_parameters);

    gm_sphere<double, 3> sp1({0, 3, -10}, 1);
    scene.add_sphere(sp1);
    

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

    
        // static const double trajectory_radius = main_pars.light_src_center.get_xy_radius_len();
        // update_light_src_position(main_pars.light_src_center, ANIMATION_SPEED, trajectory_radius);

        fill_pixel_bufer(window_pixel_bufer, scene);
        window.draw(window_pixel_bufer.data(), window_pixel_bufer.size(), sf::PrimitiveType::Points);

        window.display();
    }
}
