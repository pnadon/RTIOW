//
//  main.cpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-05-07.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#include <iostream>
#include "sphere.hpp"
#include "moving_sphere.hpp"
#include "hitablelist.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "scenes.hpp"

const float COLOR_MAX = 255.99;

int ppm_cap(int color) {
    return (color > 255 ? 255 : color );
}

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return emitted + attenuation * color(scattered, world, depth + 1);
        } else {
            return emitted;
        }
    }
    else {
        //vec3 unit_direction = unit_vec(r.direction());
        //float t = 0.5 * (unit_direction.y() + 1.0);
        //return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
        
        return vec3(0, 0, 0);
    }
}

int main() {
    int nx = 200;
    int ny = 200;
    int ns = 40;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *world = final();
    
    vec3 look_from(278, 278, -800);
    vec3 look_at(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;
    
    camera cam(look_from,
               look_at,
               vec3(0, 1, 0),
               vfov,
               float(nx) / float(ny),
               aperture,
               dist_to_focus,
               0.0,
               1.0
               );
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i +drand48()) / float(nx);
                float v = float(j +drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(COLOR_MAX * col[0]);
            int ig = int(COLOR_MAX * col[1]);
            int ib = int(COLOR_MAX * col[2]);
            std::cout << ppm_cap(ir) << " " << ppm_cap(ig) << " " << ppm_cap(ib) << "\n";
        }
    }
}
