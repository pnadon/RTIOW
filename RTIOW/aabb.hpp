//
//  aabb.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-21.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef aabb_hpp
#define aabb_hpp

#include "ray.hpp"
#include "hitable.hpp"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class aabb {
public:
    aabb() {}
    aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }
    
    vec3 min() const { return _min; }
    vec3 max() const { return _max; }
    
    bool hit(const ray& r, float tmin, float tmax) const {
        for (int a = 0; a < 3; a++) {
            float t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],
                             (_max[a] - r.origin()[a]) / r.direction()[a]);
            float t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],
                             (_max[a] - r.origin()[a]) / r.direction()[a]);
            tmin = ffmax(t0, tmin);
            tmax = ffmin(t1, tmax);
            if (tmax <= tmin) {
                return false;
            }
        }
        return true;
    }
    vec3 _min;
    vec3 _max;
};

aabb surrounding_box(aabb box0, aabb box1) {
    vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    vec3 big(fmin(box0.max().x(), box1.max().x()),
               fmin(box0.max().y(), box1.max().y()),
               fmin(box0.max().z(), box1.max().z()));
    return aabb(small, big);
}


#endif /* aabb_hpp */