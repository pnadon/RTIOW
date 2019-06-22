//
//  scenes.hpp
//  RTIOW
//
//  Created by Philippe Nadon on 2019-06-21.
//  Copyright © 2019 Philippe Nadon. All rights reserved.
//

#ifndef scenes_hpp
#define scenes_hpp
#include "sphere.hpp"
#include "moving_sphere.hpp"
#include "material.hpp"
#include "bvh.hpp"
#include "texture.hpp"
#include "rect.hpp"
#include "box.hpp"
#include "constant_medium.hpp"

hitable *random_scene() {
    int n = 50000;
    hitable **list = new hitable*[n + 1];
    texture *checker = new checker_texture( new constant_texture(vec3(0.2, 0.3, 0.1)),
                                           new constant_texture(vec3(0.9, 0.9, 0.9)));
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian( checker));
    int i = 1;
    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            float choose_mat = drand48();
            vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - vec3(4.0, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    list[i++] = new moving_sphere(center,
                                                  center + vec3(0, 0.5 * drand48(), 0),
                                                  0.0, 1.0, 0.2,
                                                  new lambertian(new constant_texture(vec3(drand48() * drand48(),
                                                                                           drand48() * drand48(),
                                                                                           drand48() * drand48()
                                                                                           )
                                                                                      )
                                                                 ));
                }
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center,
                                           0.2,
                                           new metal(vec3(0.5 * (1 + drand48()),
                                                          0.5 * (1 + drand48()),
                                                          0.5 * (1 + drand48())
                                                          ),
                                                     0.5 * drand48()
                                                     )
                                           );
                }
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0, 1, 0),
                           1.0,
                           new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0),
                           1.0,
                           new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec3(4, 1, 0),
                           1.0,
                           new metal(vec3(0.7, 0.6, 0.5), 0.0));
    
    return new hitable_list(list, i);
    //return new bvh_node(list,i, 0.0, 1.0);
}

hitable *two_spheres() {
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)),
                                           new constant_texture(vec3(0.9, 0.9, 0.9)));
    int n = 50;
    hitable **list = new hitable*[n + 1];
    list[0] = new sphere(vec3(0, -10, 0), 10, new lambertian(checker));
    list[1] = new sphere(vec3(0, 10, 0), 10, new lambertian(checker));
    
    return new hitable_list(list, 2);
}

hitable *two_perlin_spheres() {
    texture *pertext = new noise_texture(5);
    hitable **list = new hitable*[2];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
    return new hitable_list(list, 2);
}

hitable *simple_light() {
    texture *pertext = new noise_texture(4);
    hitable **list = new hitable*[4];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
    list[2] = new sphere(vec3(0, 7, 0), 2,
                         new diffuse_light(new constant_texture(vec3(4, 4, 4))));
    list[3] = new xy_rect(3, 5, 1, 3, -2,
                          new diffuse_light(new constant_texture(vec3(4, 4, 4))));
    return new hitable_list(list, 4);
}

hitable *cornell_box() {
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));
    
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 277, 332, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    
    list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0),
                                                   vec3(165, 165, 165),
                                                   white),
                                           -18),
                              vec3(130, 0, 65));
    list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0),
                                                   vec3(165, 330, 165),
                                                   white),
                                           15),
                              vec3(265, 0, 295));
    
    return new hitable_list(list, i);
}

hitable *cornell_smoke() {
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(7, 7, 7)));
    
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 277, 332, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    
    hitable *b1 = new translate(new rotate_y(new box(vec3(0, 0, 0),
                                                     vec3(165, 165, 165),
                                                     white),
                                             -18),
                                vec3(130, 0, 65));
    hitable *b2 = new translate(new rotate_y(new box(vec3(0, 0, 0),
                                                     vec3(165, 330, 165),
                                                     white),
                                             15),
                                vec3(265, 0, 295));
    list[i++] = new constant_medium(b1, 0.01, new constant_texture(vec3(1.0, 1.0, 1.0)));
    list[i++] = new constant_medium(b2, 0.01, new constant_texture(vec3(0.0, 0.0, 0.0)));
    
    return new hitable_list(list, i);
}

#endif /* scenes_hpp */
