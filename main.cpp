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
    
    .outsphere_color    = gm_vector<double, 3>(0.10, 0.10, 0.10),
    .sphere_color       = gm_vector<double, 3>(0.6, 0.1, 0.3),

    .ambient_intensity  = gm_vector<double, 3>(0.2, 0.2, 0.2),
    .defuse_intensity   = gm_vector<double, 3>(0.8, 0.7, 0.6),
    .specular_intensity = gm_vector<double, 3>(0.7, 0.7, 0),
    
    .light_src_center = gm_vector<double, 3>(25.5636, 4.74371, -1),
    .view_center      = gm_vector<double, 3>(0, 0, 5),

    .view_light_pow = 15,   
    .shadow_coef = 8,
    .pixel_scale = 1.0 / 40,
    .pixel_cordsys_offset = gm_vector<int, 2>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Sphere");
    pixel_bufer window_pixel_bufer = {WINDOW_WIDTH, WINDOW_HEIGHT};

    scene_manager scene({0, 0, 0}, main_visual_parameters);

    gm_sphere<double, 3> sp1({5, 0, -5}, 5);
    gm_sphere<double, 3> sp2({-5, 0, -5}, 4);
    scene.add_sphere(sp1);
    scene.add_sphere(sp2);
    
    double trajectory_radius = scene.get_light_src_center().get_len2();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // std::cout << "light: " << scene.get_light_src_center();

    
        scene.update_light_src_position(ANIMATION_SPEED, trajectory_radius);

        fill_pixel_bufer(window_pixel_bufer, scene);
        window.draw(window_pixel_bufer.data(), window_pixel_bufer.size(), sf::PrimitiveType::Points);

        window.display();
    }
}
