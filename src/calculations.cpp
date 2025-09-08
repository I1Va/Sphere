#include "visual.hpp"

static const geom_dot3 SPHERE_CENTER = geom_dot3(0, 0, 0);
static const double SPHERE_RADIUS = 1;


void fill_vertex_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars) {
    for (int pixel_x = 0; pixel_x < window_pixel_bufer.width; pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_pixel_bufer.height; pixel_y++) {
            pixel_dot cur_pixel = {pixel_x, pixel_y};
            geom_dot2 dot2 = convert_pixel_to_geom_dot2(cur_pixel, pars->pixel_scale, pars->pixel_cordsys_offset);

            if (!is_dot_on_sphere2(dot2, geom_dot2(SPHERE_CENTER.x, SPHERE_CENTER.y), SPHERE_RADIUS)) {
                draw_pixel(window_pixel_bufer, cur_pixel, pars->outsphere_color);
                continue;
            }

            geom_sphere3 sphere3(SPHERE_CENTER, SPHERE_RADIUS);
            geom_dot3 sphere_dot = sphere3.place_dot2_on_sphere(dot2);

            


            // vector calculations
            geom_vector3 light_vector = geom_vector3(pars->light_src_center);
            geom_vector3 onsphere_vector = geom_vector3(sphere_dot);

            geom_vector3 normal_vector = onsphere_vector;



            double light_ref_angle_cos = (!(light_vector - onsphere_vector)) ^ (normal_vector);

            double sphere_dot_light_intensity = pars->ambient_intensity + pars->light_src_intensity * light_ref_angle_cos;
            
            
            pixel_color color = {sphere_dot_light_intensity * 255, sphere_dot_light_intensity * 255, sphere_dot_light_intensity * 255};
            draw_pixel(window_pixel_bufer, cur_pixel, color);
            
        }
    }
}