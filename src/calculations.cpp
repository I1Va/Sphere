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
            // vector calculations
            geom_vector3 light_vector = geom_vector3(pars->light_src_center);
            geom_vector3 onsphere_vector = geom_vector3(sphere_dot);
            geom_vector3 normal_vector = onsphere_vector;
            double light_ref_angle_cos = std::clamp((!(light_vector - onsphere_vector)) ^ (normal_vector), -1.0, 1.0);
            double light_ref_angle = std::acos(light_ref_angle_cos);
            double sphere_dot_light_intensity = pars->light_src_intensity * light_ref_angle_cos;
            summary_intensity += sphere_dot_light_intensity;

            geom_vector3 view_vector = geom_vector3(pars->view_center);
            geom_vector3 sphere_to_light_vector = rotate_tow_vec(light_ref_angle * 2, light_vector - onsphere_vector, normal_vector);
            geom_vector3 sphere_to_view_vector = view_vector - sphere_dot;
            double view_angle_cos = (!sphere_to_light_vector) ^ (!sphere_to_view_vector);
            std:: cout << !sphere_to_light_vector << " " << !sphere_to_view_vector << "\n";
            std::cout << "cos : " << view_angle_cos << "\n";
            if (view_angle_cos > 0) {
                summary_intensity += std::pow(view_angle_cos, pars->view_light_pow);
            }

            pixel_color color = {summary_intensity * 200, summary_intensity * 200, summary_intensity * 200};
            std::cout << "color : " << color << "\n";
            draw_pixel(window_pixel_bufer, cur_pixel, color);
        }
    }
}