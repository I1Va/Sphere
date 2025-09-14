#include "visual.hpp"
#include <algorithm>
#include <cfloat>
#include "scene.hpp"


gm_vector<double, 3> get_pixel_3d_pos(const gm_vector<int, 2> &pixel, const scene_manager &scene) {
    gm_vector<double, 3> pixel_3d_pos(pixel.get_x(), pixel.get_y(), scene.get_screen_pos().get_z());

    pixel_3d_pos -= scene.get_pixel_cordsys_offset().to_3d();
    pixel_3d_pos *= scene.get_pixel_scale();

    return pixel_3d_pos;
}

// geom_vector3 get_defuse_light_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_vector3 &defuse_intensity) {
//     geom_vector3 normal_vec = onsphere_vec;

//     double light_ref_angle_cos = (!(sphere_to_light_vec)) ^ (!normal_vec);

//     if (light_ref_angle_cos > 0)
//         return defuse_intensity * light_ref_angle_cos;
//     return geom_vector3(0, 0, 0);
// }

// geom_vector3 get_specular_intensity(geom_vector3 &sphere_to_light_vec, geom_vector3 &onsphere_vec, geom_dot3 &view_center, 
//                                     geom_vector3& intensity, double view_light_pow) {
//     geom_vector3 sphere_to_refl_light_vec = sphere_to_light_vec - get_ortogonal(sphere_to_light_vec, onsphere_vec) * 2;
    
//     geom_vector3 sphere_to_view_vec = geom_vector3(view_center) - onsphere_vec;
//     double view_angle_cos = (!sphere_to_refl_light_vec) ^ (!sphere_to_view_vec);


//     geom_vector3 res_intensity = intensity * std::pow(view_angle_cos, view_light_pow); 
//     // тут можно добавить учет угла брюстера
//     if (view_angle_cos > 0)
//         return res_intensity;
        
//     return geom_vector3(0, 0, 0);        
// }

void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const scene_manager &scene) {
    for (int pixel_x = 0; pixel_x < window_pixel_bufer.get_width(); pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_pixel_bufer.get_height(); pixel_y++) {
            gm_vector<int, 2> pixel(pixel_x, pixel_y);

            gm_vector<double, 3> point = get_pixel_3d_pos(pixel, scene);

            gm_vector<double, 3> camera_pos = scene.get_camera_pos();
            gm_vector<double, 3> camera_ray_direction = point - camera_pos;

            gm_line<double, 3> camera_ray(camera_pos, camera_ray_direction);
            
            gm_vector<double, 3> sphere_point = scene.get_closest_sphere_intersection(camera_ray);

       
            if (sphere_point.is_poison()) {
                draw_pixel(window_pixel_bufer, pixel, scene.get_outsphere_color());
                continue;
            }
            
            draw_pixel(window_pixel_bufer, pixel, scene.get_sphere_color());


            // geom_vector3 light_vec = geom_vector3(pars.light_src_center);
            // geom_vector3 onsphere_vec = geom_vector3(sphere_dot);
            // geom_vector3 sphere_to_light_vec = light_vec - onsphere_vec;
    

            // geom_vector3 summary_intensity = cord_mul(scene.get_ambient_intensity(), scene.get_sphere_color());
            // summary_intensity += cord_mul(get_defuse_light_intensity(light_vec, onsphere_vec, pars.defuse_intensity),
            //                               pars.sphere_color);

            // summary_intensity += get_specular_intensity(light_vec, onsphere_vec, pars.view_center, 
            //                                              pars.specular_intensity, pars.view_light_pow);

            // summary_intensity = summary_intensity.clamp(0.0, 1.0);

            // draw_pixel(window_pixel_bufer, cur_pixel, summary_intensity);
        }
    }
}

// void update_light_src_position(geom_dot3 &light_src_center, double speed_coef, double radius) {
//     static double cur_radians = std::acos(light_src_center.get_x() / radius);
//     cur_radians += M_PI * 2 * speed_coef;

//     light_src_center = geom_dot3
//     (
//         radius * std::cos(cur_radians),
//         radius * std::sin(cur_radians),
//         light_src_center.get_z()
//     );
// }
