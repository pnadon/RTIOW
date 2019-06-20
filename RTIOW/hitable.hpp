//
//  hitable.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-05.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* hitable_hpp */
