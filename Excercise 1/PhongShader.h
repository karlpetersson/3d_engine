//
//  PhongShader.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__PhongShader__
#define __Excercise_1__PhongShader__

#include <iostream>
#include "ShaderProgram.h"
#include <vector>

class PhongShader : public ShaderProgram {
private:
    GLuint materialsBuffer;
    std::vector<GLuint> lightBuffers;
    GLuint lightsBuffer;
    void initMaterials();
    void initLights();
public:
    enum {
        MATERIAL_BINDING_POINT = 0,
        LIGHT_BINDING_POINT = 1
    };
    PhongShader();
    void prepare(Scene *scene, Camera *camera, Mesh *mesh);
};

#endif /* defined(__Excercise_1__PhongShader__) */
