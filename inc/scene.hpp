#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "gm_primitives.hpp"


class scene_manager {
    const gm_vector<double, 3> CAMERA_DELTA = gm_vector<double, 3>(0, 0, 10);
    
    std::vector<gm_sphere<double, 3>> objects;

    gm_vector<double, 3> screen_pos;
    gm_vector<double, 3> camera_pos;

    gm_vector<double, 3> sphere_color;
    gm_vector<double, 3> outsphere_color;

    gm_vector<double, 3> ambient_intensity;
    gm_vector<double, 3> defuse_intensity;
    gm_vector<double, 3> specular_intensity;

    gm_vector<double, 3> light_src_center;
    
    double view_light_pow;
    double shadow_coef;
    double pixel_scale;
    gm_vector<int, 2> pixel_cordsys_offset;  

public:
    scene_manager(
        gm_vector<double, 3> screen_pos,
        visual_parameters pars
    ):
        screen_pos(screen_pos),
        camera_pos(screen_pos + CAMERA_DELTA),
        
        sphere_color(pars.sphere_color),
        outsphere_color(pars.outsphere_color),

        ambient_intensity(pars.defuse_intensity),
        defuse_intensity(pars.defuse_intensity),
        specular_intensity(pars.specular_intensity),
        light_src_center(pars.light_src_center),

        view_light_pow(pars.view_light_pow),
        shadow_coef(pars.shadow_coef),
        pixel_scale(pars.pixel_scale),
        pixel_cordsys_offset(pars.pixel_cordsys_offset)
    {}
        
    void add_sphere(gm_sphere<double, 3> sphere) { objects.push_back(sphere); }

    bool get_closest_sphere_intersection(
            const gm_line<double, 3> &ray, 
            gm_vector<double, 3> *closest_intersection, int *res_sphere_idx, const int except_sphere_idx = -1) const 
    {
        *closest_intersection = gm_vector<double, 3>::POISON();
        *res_sphere_idx = -1;
    
        double distance2 = NAN;

        for (int idx = 0; idx < objects.size(); idx++) {
            if (idx == except_sphere_idx) continue;

            gm_sphere<double, 3> cur_sphere = objects[idx];
    
            gm_vector<double, 3> intersection_point = cur_sphere.get_closest_intersection(ray);
            if (intersection_point.is_poison()) continue;


            double cur_distance2 = (intersection_point - ray.get_start()).get_len2();

            if (std::isnan(distance2) || cur_distance2 < distance2) {
                distance2 = cur_distance2;
                *closest_intersection = intersection_point;
                *res_sphere_idx = idx;
            }
        }

        return (*res_sphere_idx != -1);
    }

    // double get_closest_sphere_distance2(const gm_line<double, 3> &ray) const {
    //     double result_distance2 = NAN;
    //     for (gm_sphere<double, 3> sphere : objects) {
    //         double sphere_line_distance2 = get_dot_line_distance(ray, sphere.get_center());
    //         if (sphere_line_distance2 > sphere.get_radius()) 
    //             continue;
    //         if (std::isnan(result_distance2) || result_distance2 > sphere_line_distance2)
    //             result_distance2 = sphere_line_distance2;
    //     }

    //     return result_distance2;
    // }


    inline gm_sphere<double, 3> get_sphere(const size_t sphere_idx) const { return objects[sphere_idx]; }
    inline gm_vector<double, 3> get_screen_pos() const { return screen_pos; }
    inline gm_vector<double, 3> get_camera_pos() const { return camera_pos; }

    inline gm_vector<double, 3> get_sphere_color() const { return sphere_color; }
    inline gm_vector<double, 3> get_outsphere_color() const { return outsphere_color; }

    inline gm_vector<double, 3> get_ambient_intensity() const { return ambient_intensity; }
    inline gm_vector<double, 3> get_defuse_intensity() const { return defuse_intensity; }
    inline gm_vector<double, 3> get_specular_intensity() const { return specular_intensity; }

    inline gm_vector<double, 3> get_light_src_center() const { return light_src_center; } 
    
    inline double get_view_light_pow() const { return view_light_pow; }
    inline double get_shadow_coef() const { return shadow_coef; }
    
    inline double get_pixel_scale() const { return pixel_scale; }
    inline gm_vector<int, 2> get_pixel_cordsys_offset() const { return pixel_cordsys_offset; }
    
    
    void update_light_src_position(const double speed_coef, const double radius) {

        static double cur_radians = std::acos(light_src_center.get_x() / radius);
        cur_radians += M_PI * 2 * speed_coef;

        light_src_center = gm_vector<double, 3>
        (
            radius * std::cos(cur_radians),
            radius * std::sin(cur_radians),
            light_src_center.get_z()
        );
    }
};



#endif // SCENE_HPP