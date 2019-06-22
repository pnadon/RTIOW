//
//  ray.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-05.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp
#include "vec3.hpp"

class ray {
public:
    ray() {}
    ray(const vec3& a, const vec3& b, float ti = 0.0) { A = a; B = b; _time = ti;}
    
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    float time() const { return _time; }
    vec3 point(float t) const { return A + t * B; }
    
    vec3 A;
    vec3 B;
    float _time;
};

#endif /* ray_hpp */
