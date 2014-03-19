//
//  PhongShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//


#include "DeferredPhongShader.h"

DeferredPhongShader::DeferredPhongShader() {
    this->id = ShaderManager::getInstance().load(PROJECT_PATH + "pointLightDeferredPhong.vs", PROJECT_PATH + "pointLightDeferredPhong.fs");
    
    init();
    
    glLinkProgram(this->id);
    
    normalTextureSamplerLocation = glGetUniformLocation(this->id, "tex_normal");
    diffuseTextureSamplerLocation = glGetUniformLocation(this->id, "tex_diffuse");
    ambientTextureSamplerLocation = glGetUniformLocation(this->id, "tex_ambient");
    specularTextureSamplerLocation = glGetUniformLocation(this->id, "tex_specular");
    shininessTextureSamplerLocation = glGetUniformLocation(this->id, "tex_shininess");
    depthTextureSamplerLocation = glGetUniformLocation(this->id, "tex_depth");
    
    inverseProjectionLocation = glGetUniformLocation(this->id, "m_inverseProjection");
    inverseViewLocation = glGetUniformLocation(this->id, "m_inverseView");
    
    initLights();
    
    
}

void DeferredPhongShader::prepare(Scene *scene, Camera *camera, Light *light) {
    
    ShaderProgram::prepare(camera);
    
    glUniformMatrix4fv(inverseProjectionLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->projection)));
    glUniformMatrix4fv(inverseViewLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->view)));
    
    glUniform1i(normalTextureSamplerLocation, TEXTURE_TYPE_NORMAL);
    glUniform1i(depthTextureSamplerLocation, TEXTURE_TYPE_DEPTH);
    glUniform1i(diffuseTextureSamplerLocation, TEXTURE_TYPE_DIFFUSE);
    glUniform1i(ambientTextureSamplerLocation, TEXTURE_TYPE_AMBIENT);
    glUniform1i(specularTextureSamplerLocation, TEXTURE_TYPE_SPECULAR);
    glUniform1i(shininessTextureSamplerLocation, TEXTURE_TYPE_SHININESS);
    
    // upload light data to gpu
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    //for (std::vector<Light *>::iterator it = scene->lights.begin() ; it != scene->lights.end(); it++) {
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &light->data, GL_DYNAMIC_DRAW);
    //}
}

// initializes buffer for light uniform
void DeferredPhongShader::initLights() {
    GLuint blockIndex = glGetUniformBlockIndex(id, "Light");
    if(blockIndex == GL_INVALID_INDEX) {
        throw "Invalid uniform block index";
    }
    
    GLuint bindingPoint = DeferredPhongShader::LIGHT_BINDING_POINT;
    
    glUniformBlockBinding(id, blockIndex, bindingPoint);
    
    glGenBuffers(1, &lightsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, lightsBuffer);
    
}
