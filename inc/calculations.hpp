#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "visual.hpp"
#include "scene.hpp"


void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const scene_manager &scene);

gm_vector<double, 3> get_pixel_3d_pos(const gm_vector<int, 2> &pixel, const scene_manager &scene);

// gm_vector<double, 3>  get_defuse_light_intensity(gm_vector<double, 3> sphere_to_light_vec, gm_vector<double, 3> sphere_normal_vec, 
//                                                  gm_vector<double, 3> defuse_intensity);

// gm_vector<double, 3> get_specular_intensity(
//     gm_vector<double, 3> sphere_to_light_vec, gm_vector<double, 3> sphere_point, gm_vector<double, 3> camera_point, 
//     gm_vector<double, 3> intensity, double view_light_pow);


#endif // CALCULATIONS_HPP
