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

class camera {
public:
    camera() {
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horiz = vec3(4.0, 0.0, 0.0);
        vert = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner + u * horiz + v * vert - origin);
    }
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horiz;
    vec3 vert;
};

#endif /* camera_hpp */
