//
//  Object3D.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Object3D__
#define __Excercise_1__Object3D__

#include <iostream>
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Scene;

class Object3D {
public:
    
    glm::mat4 modelMatrix;
    
    Object3D();
    void translate(glm::vec3 vector);
    void rotate(glm::vec3 vector, float degrees);
    void scale(glm::vec3 vector);
    virtual void render(Scene *scene) {};
};

#endif /* defined(__Excercise_1__Object3D__) */
