#include "visual.hpp"
#include <algorithm>
#include <cfloat>
#include "scene.hpp"


gm_vector<double, 3> get_pixel_3d_pos(const gm_vector<int, 2> &pixel, const scene_manager &scene) {
    gm_vector<double, 3> pixel_3d_pos(pixel.get_x(), pixel.get_y(), scene.get_screen_pos().get_z());

    pixel_3d_pos -= scene.get_pixel_cordsys_offset().to_3d();
    pixel_3d_pos = cord_mul(pixel_3d_pos, gm_vector<double, 3>(1, -1, 1));
    pixel_3d_pos *= scene.get_pixel_scale();

    return pixel_3d_pos;
}

gm_vector<double, 3>  get_defuse_light_intensity(gm_vector<double, 3> sphere_to_light_vec, gm_vector<double, 3> sphere_normal_vec, gm_vector<double, 3> defuse_intensity) {
    double light_ref_angle_cos = (!(sphere_to_light_vec)).scalar_product(!sphere_normal_vec);

    if (light_ref_angle_cos > 0)
        return defuse_intensity * light_ref_angle_cos;
    return gm_vector<double, 3>(0, 0, 0);
}

gm_vector<double, 3> get_specular_intensity(
    gm_vector<double, 3> sphere_to_light_vec, gm_vector<double, 3> sphere_point, gm_vector<double, 3> sphere_center, gm_vector<double, 3> camera_point, 
    gm_vector<double, 3> intensity, double view_light_pow) 
{
    gm_vector<double, 3> sphere_to_refl_light_vec = sphere_to_light_vec - get_ortogonal(sphere_to_light_vec, sphere_point - sphere_center) * 2;
    
    gm_vector<double, 3> sphere_to_view_vec = camera_point - sphere_point;
    double view_angle_cos = (!sphere_to_refl_light_vec).scalar_product(!sphere_to_view_vec);

    if (view_angle_cos > 0) {
        gm_vector<double, 3> res_intensity = intensity * std::pow(view_angle_cos, view_light_pow); 
        return res_intensity;
    }
        
    return gm_vector<double, 3>(0, 0, 0);        
}

double get_shadow_factor(const gm_vector<double, 3> &sphere_point, const int sphere_idx, const scene_manager &scene) {
    gm_line<double, 3> sphere_to_light_ray(sphere_point, scene.get_light_src_center() - sphere_point);

    int shadow_sphere_idx = -1;
    gm_vector<double, 3> shadow_sphere_point = gm_vector<double, 3>::POISON();
    bool intersection_state = scene.get_closest_sphere_intersection(sphere_to_light_ray, &shadow_sphere_point, &shadow_sphere_idx, sphere_idx);

    if (shadow_sphere_idx == -1) {
        return 1.0;
    }

    gm_sphere<double, 3> shadow_sphere = scene.get_sphere(shadow_sphere_idx);
    double shadow_distance = shadow_sphere.get_distance2_to_line(sphere_to_light_ray) / (shadow_sphere.get_radius() * shadow_sphere.get_radius());

    return 1.0 / (1 + std::exp(-scene.get_shadow_coef() * (shadow_distance - 0.5)));
}

void fill_pixel_bufer(pixel_bufer &window_pixel_bufer, const scene_manager &scene) {
    for (int pixel_x = 0; pixel_x < window_pixel_bufer.get_width(); pixel_x++) {
        for (int pixel_y = 0; pixel_y < window_pixel_bufer.get_height(); pixel_y++) {
            gm_vector<int, 2> pixel(pixel_x, pixel_y);

            gm_vector<double, 3> point = get_pixel_3d_pos(pixel, scene);

            gm_vector<double, 3> camera_pos = scene.get_camera_pos();
            gm_vector<double, 3> camera_ray_direction = point - camera_pos;

            gm_line<double, 3> camera_ray(camera_pos, camera_ray_direction);
            

            int intersection_sphere_idx = -1;
            gm_vector<double, 3> sphere_point = gm_vector<double, 3>::POISON();
            bool intersection_state = scene.get_closest_sphere_intersection(camera_ray, &sphere_point, &intersection_sphere_idx);

            if (!intersection_state) {
                draw_pixel(window_pixel_bufer, pixel, scene.get_outsphere_color());
                continue;
            }
            
            assert(intersection_sphere_idx != -1);
            assert(!sphere_point.is_poison());

            gm_sphere<double, 3> sphere = scene.get_sphere(intersection_sphere_idx);
            gm_vector<double, 3> light_point = scene.get_light_src_center();
            gm_vector<double, 3> sphere_normal_vec = sphere_point - sphere.get_center();


            
            gm_vector<double, 3> sphere_to_light_vec = light_point - sphere_point;
    

            gm_vector<double, 3> ambient_intensity = cord_mul(scene.get_ambient_intensity(), scene.get_sphere_color());
            
            
            gm_vector<double, 3> defuse_intensity = cord_mul(
                get_defuse_light_intensity(sphere_to_light_vec, sphere_normal_vec, scene.get_defuse_intensity()),
                scene.get_sphere_color()
            );

            gm_vector<double, 3> specular_intensity = get_specular_intensity(sphere_to_light_vec, sphere_point, sphere.get_center(), camera_pos, 
                                                         scene.get_specular_intensity(), scene.get_view_light_pow());
            

            double shadow_factor = 1;                                             
            if (!(defuse_intensity == gm_vector<double, 3>(0, 0, 0))) {
                shadow_factor = get_shadow_factor(sphere_point, intersection_sphere_idx, scene);
            }
            
            
            gm_vector<double, 3> summary_intensity = gm_vector<double, 3>(0, 0, 0);

           summary_intensity = 
                ambient_intensity + 
                (defuse_intensity + specular_intensity ) * shadow_factor;

            summary_intensity = summary_intensity.clamp(0.0, 1.0);
            draw_pixel(window_pixel_bufer, pixel, summary_intensity);
        }
    }
}