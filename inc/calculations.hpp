#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "visual.hpp"
#include "scene.hpp"


// // geom_vector3 get_defuse_light_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_vector3 &defuse_intensity);
// // geom_vector3 get_specular_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_dot3 &view_center, double view_light_pow);

void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const scene_manager &scene);

// // void update_light_src_position(geom_dot3 &light_src_center, double speed_coef, double radius);


#endif // CALCULATIONS_HPP
