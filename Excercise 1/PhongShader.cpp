//
//  PhongShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "PhongShader.h"

PhongShader::PhongShader() {
    this->id = ShaderManager::getInstance().load(PROJECT_PATH + "lightPass.vs", PROJECT_PATH + "lightPass.fs");
    
    init();
    glLinkProgram(this->id);

    initLights();
    
    inverseProjectionLocation = glGetUniformLocation(this->id, "m_inverseProjection");
    inverseViewLocation = glGetUniformLocation(this->id, "m_inverseView");
    normalTextureSamplerLocation = glGetUniformLocation(this->id, "tex_normal");
    diffuseTextureSamplerLocation = glGetUniformLocation(this->id, "tex_diffuse");
    ambientTextureSamplerLocation = glGetUniformLocation(this->id, "tex_ambient");
    specularTextureSamplerLocation = glGetUniformLocation(this->id, "tex_shininess");
    shininessTextureSamplerLocation = glGetUniformLocation(this->id, "tex_specular");
    depthTextureSamplerLocation = glGetUniformLocation(this->id, "tex_depth");

}

void PhongShader::prepare(Scene *scene, Camera *camera) {
    
    ShaderProgram::prepare(camera);

    glUniformMatrix4fv(inverseProjectionLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->projection)));
    glUniformMatrix4fv(inverseViewLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(camera->view)));

    glUniform1i(normalTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_SHININESS);
    glUniform1i(diffuseTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
    glUniform1i(ambientTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_AMBIENT);
    glUniform1i(specularTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    glUniform1i(shininessTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glUniform1i(depthTextureSamplerLocation, GBuffer::GBUFFER_TEXTURE_TYPE_DEPTH);
    
    // upload light data to gpu
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    for (std::vector<Light *>::iterator it = scene->lights.begin() ; it != scene->lights.end(); it++) {
        glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &(*it)->data, GL_DYNAMIC_DRAW);
    }
}

// initializes buffer for light uniform
void PhongShader::initLights() {
    GLuint blockIndex = glGetUniformBlockIndex(id, "Light");
    if(blockIndex == GL_INVALID_INDEX) {
        throw "Invalid uniform block index";
    }

    GLuint bindingPoint = PhongShader::LIGHT_BINDING_POINT;
    
    glUniformBlockBinding(id, blockIndex, bindingPoint);
    
    glGenBuffers(1, &lightsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, lightsBuffer);
  
}
