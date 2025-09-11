#include "visual.hpp"
#include <algorithm>
#include <cfloat>

static const geom_dot3 SPHERE_CENTER = geom_dot3(0, 0, 0);
static const double SPHERE_RADIUS = 1;

inline geom_vector3 convert_color_into_geomvec3(const pixel_color &color) {
    return geom_vector3(color.r, color.g, color.b);
};

geom_vector3 get_defuse_light_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_vector3 &defuse_intensity) {
    geom_vector3 normal_vec = onsphere_vec;

    double light_ref_angle_cos = (!(sphere_to_light_vec)) ^ (!normal_vec);

    if (light_ref_angle_cos > 0)
        return defuse_intensity * light_ref_angle_cos;
    return geom_vector3(0, 0, 0);
}

geom_vector3 get_specular_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_dot3 &view_center, 
                                    geom_vector3& intensity, double view_light_pow) {
    geom_vector3 sphere_to_refl_light_vec = sphere_to_light_vec - get_ortogonal(sphere_to_light_vec, onsphere_vec) * 2;
    
    geom_vector3 sphere_to_view_vec = geom_vector3(view_center) - onsphere_vec;
    double view_angle_cos = (!sphere_to_refl_light_vec) ^ (!sphere_to_view_vec);


    geom_vector3 res_intensity = intensity * std::pow(view_angle_cos, view_light_pow); 
    // тут можно добавить учет угла брюстера
    if (view_angle_cos > 0)
        return res_intensity;
        
    return geom_vector3(0, 0, 0);        
}

void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, visual_parameters &pars) {
    for (int pixel_x = 0; pixel_x < window_pixel_bufer.get_width(); pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_pixel_bufer.get_height(); pixel_y++) {
            pixel_dot cur_pixel = pixel_dot(pixel_x, pixel_y);
            geom_dot2 dot2 = convert_pixel_to_geom_dot2(cur_pixel, pars.pixel_scale, pars.pixel_cordsys_offset);

            if (!is_dot_on_sphere2(dot2, geom_dot2(SPHERE_CENTER.get_x(), SPHERE_CENTER.get_y()), SPHERE_RADIUS)) {
                draw_pixel(window_pixel_bufer, cur_pixel, pars.outsphere_color);
                continue;
            }

            geom_sphere3 sphere3(SPHERE_CENTER, SPHERE_RADIUS);
            geom_dot3 sphere_dot = sphere3.place_dot2_on_sphere(dot2);


            geom_vector3 light_vec = geom_vector3(pars.light_src_center);
            geom_vector3 onsphere_vec = geom_vector3(sphere_dot);
            geom_vector3 sphere_to_light_vec = light_vec - onsphere_vec;
    

            geom_vector3 summary_intensity = cord_mul(pars.ambient_intensity, pars.sphere_color);
            summary_intensity += cord_mul(get_defuse_light_intensity(light_vec, onsphere_vec, pars.defuse_intensity),
                                          pars.sphere_color);

            summary_intensity += get_specular_intensity(light_vec, onsphere_vec, pars.view_center, 
                                                         pars.specular_intensity, pars.view_light_pow);

            summary_intensity = summary_intensity.clamp(0.0, 1.0);

            draw_pixel(window_pixel_bufer, cur_pixel, summary_intensity);
        }
    }
}

void update_light_src_position(geom_dot3 &light_src_center, double speed_coef, double radius) {
    static double cur_radians = std::acos(light_src_center.get_x() / radius);
    cur_radians += M_PI * 2 * speed_coef;

    light_src_center = geom_dot3
    (
        radius * std::cos(cur_radians),
        radius * std::sin(cur_radians),
        light_src_center.get_z()
    );
}
