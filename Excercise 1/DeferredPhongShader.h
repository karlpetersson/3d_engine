//
//  PhongShader.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__DeferredPhongShader__
#define __Excercise_1__DeferredPhongShader__

#include <iostream>
#include "ShaderProgram.h"
#include <vector>

class DeferredPhongShader : public ShaderProgram {
private:
    GLuint materialsBuffer;
    std::vector<GLuint> lightBuffers;
    GLuint lightsBuffer;
    void initMaterials();
    void initLights();
public:
    enum {
        MATERIAL_BINDING_POINT = 4,
        LIGHT_BINDING_POINT = 5
    };
    DeferredPhongShader();
    void prepare(Scene *scene, Camera *camera, Mesh *mesh);
};

#endif /* defined(__Excercise_1__DeferredPhongShader__) */
