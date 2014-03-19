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
#include "GBuffer.h"
#include <vector>

class DeferredPhongShader : public ShaderProgram {
private:
    GLuint materialsBuffer;
    std::vector<GLuint> lightBuffers;
    GLuint lightsBuffer;
    
    GLint inverseProjectionLocation;
    GLint inverseViewLocation;
    GLint normalTextureSamplerLocation;
    GLint diffuseTextureSamplerLocation;
    GLint ambientTextureSamplerLocation;
    GLint specularTextureSamplerLocation;
    GLint shininessTextureSamplerLocation;
    GLint depthTextureSamplerLocation;
    
    void initMaterials();
    void initLights();
public:
    enum {
        LIGHT_BINDING_POINT = 1
    };
    DeferredPhongShader();
    void prepare(Scene *scene, Camera *camera, Light *light);
};

#endif /* defined(__Excercise_1__DeferredPhongShader__) */