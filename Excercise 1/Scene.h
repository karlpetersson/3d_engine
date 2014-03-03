//
//  Scene.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Scene__
#define __Excercise_1__Scene__

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Mesh.h"
#include "Light.h"

class Scene {
public:
    glm::mat4 projection;
    glm::mat4 view;
    std::vector<Mesh *> objects;
    std::vector<Light *> lights;
    
    Scene();
    void add(Mesh *obj);
    void add(Light *light);
};

#endif /* defined(__Excercise_1__Scene__) */
