#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "visual.hpp"


void fill_vertex_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars);
void update_light_src_position(geom_dot3 *light_src_center, double speed_coef, double radius);


#endif // CALCULATIONS_HPP