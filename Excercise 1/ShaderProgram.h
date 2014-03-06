//
//  ShaderProgram.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__ShaderProgram__
#define __Excercise_1__ShaderProgram__

#include <iostream>
#include "ShaderManager.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "Scene.h"
#include "Mesh.h"
#include "constants.h"
#include "Camera.h"

class ShaderProgram {
protected:
    int id;
    void init();
public:
    ShaderProgram() {};
    void use();
    void prepare(Camera *camera);
    GLuint getId();
};

#endif /* defined(__Excercise_1__ShaderProgram__) */
