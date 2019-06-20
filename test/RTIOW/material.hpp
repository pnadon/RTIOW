//
//  lambertian.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-05.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include "ray.hpp"
#include "hitable.hpp"

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.sqr_length() >= 1.0);
    return p;
}

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attentuation, ray& scattered) const = 0;
};

class lambertian: public material {
public:
    lambertian(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};

class metal: public material {
public:
    metal(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vec(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
    vec3 albedo;
};

#endif /* material_hpp */
