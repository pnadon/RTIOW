//
//  camera.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-05.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "ray.hpp"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

class camera {
public:
    camera(vec3 look_from,
           vec3 look_at,
           vec3 v_up,
           float vfov,
           float aspect,
           float aperture,
           float focus_dist) {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = look_from;
        w = unit_vec(look_from - look_at);
        u = unit_vec(cross(v_up, w));
        v = cross(w, u);
        lower_left_corner = origin - focus_dist * (
                                                   half_width * u
                                                   + half_height * v
                                                   + w
                                                   );
        horiz = 2 * half_width * focus_dist * u;
        vert = 2 * half_height * focus_dist * v;
    }
    ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin,
                   lower_left_corner + s * horiz + t * vert - origin - offset);
    }
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horiz;
    vec3 vert;
    vec3 u, v, w;
    float lens_radius;
};

#endif /* camera_hpp */
