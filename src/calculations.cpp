#include "visual.hpp"


void fill_vertex_bufer(pixel_bufer &window_pixel_bufer, const visual_parameters *pars) {
    for (int pixel_x = 0; pixel_x < window_pixel_bufer.width; pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_pixel_bufer.height; pixel_y++) {
            pixel_dot cur_pixel = {pixel_x, pixel_y};
            geom_dot2 dot2 = convert_pixel_to_geom_dot2(cur_pixel, pars->pixel_scale, pars->pixel_cordsys_offset);

            if (!is_dot_on_sphere2(dot2, geom_dot2(pars->sphere_center.x, pars->sphere_center.y), pars->sphere_radius)) {
                draw_pixel(window_pixel_bufer, cur_pixel, pars->outsphere_color);
                continue;
            }

            geom_sphere3 sphere3(pars->sphere_center, pars->sphere_radius);
            geom_dot3 sphere_dot = sphere3.place_dot2_on_sphere(dot2);

            pixel_color color = {32 + sphere_dot.z * 100, 32 + sphere_dot.z * 100, 32 + sphere_dot.z * 100};
            draw_pixel(window_pixel_bufer, cur_pixel, color);
            
        }
    }
}