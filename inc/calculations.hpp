#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "visual.hpp"


geom_vector3 get_absent_light_intensity(const geom_vector3 &sphere_to_light_vec, const geom_vector3 &onsphere_vec, const geom_vector3 &light_src_intensity);
geom_vector3 get_glare_intension(const geom_vector3 &sphere_to_light_vec, const geom_vector3 &onsphere_vec, const geom_dot3 &view_center, const double view_light_pow);
void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars);
void update_light_src_position(geom_dot3 *light_src_center, double speed_coef, double radius);


#endif // CALCULATIONS_HPP
