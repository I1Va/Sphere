#include "visual.hpp"
#include <algorithm>
#include <cfloat>

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


            double summary_intensity = pars->ambient_intensity;

            geom_vector3 light_vec = geom_vector3(pars->light_src_center);
            geom_vector3 onsphere_vec = geom_vector3(sphere_dot);
            geom_vector3 sphere_to_light_vec = light_vec - onsphere_vec;
            geom_vector3 normal_vec = onsphere_vec;

            double light_ref_angle_cos = (!(sphere_to_light_vec)) ^ (!normal_vec);

            if (light_ref_angle_cos > 0) { 
                double sphere_absent_light_intensity = pars->light_src_intensity * light_ref_angle_cos;
                summary_intensity += sphere_absent_light_intensity;
            }
            

            
            geom_vector3 sphere_to_refl_light_vec = sphere_to_light_vec - get_ortogonal(sphere_to_light_vec, normal_vec) * 2;
            
            geom_vector3 sphere_to_view_vec = geom_vector3(pars->view_center) - onsphere_vec;
            double view_angle_cos = (!sphere_to_refl_light_vec) ^ (!sphere_to_view_vec);
            
            if (view_angle_cos > 0)
                summary_intensity += std::pow(view_angle_cos, pars->view_light_pow);
        
            pixel_color color = {int(summary_intensity * 150), int(summary_intensity * 150), int(summary_intensity * 150)};
            draw_pixel(window_pixel_bufer, cur_pixel, color);
        }
    }
}

void update_light_src_position(geom_dot3 *light_src_center, double speed_coef, double radius) {
    assert(light_src_center);

    static double cur_radians = std::acos(light_src_center->x / radius);
    cur_radians += M_PI * 2 * speed_coef;

    *light_src_center = geom_dot3
    (
        radius * std::cos(cur_radians),
        radius * std::sin(cur_radians),
        light_src_center->z
    );
}