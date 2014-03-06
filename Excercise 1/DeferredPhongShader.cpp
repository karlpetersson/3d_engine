//
//  PhongShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "DeferredPhongShader.h"

DeferredPhongShader::DeferredPhongShader() {
    this->id = ShaderManager::getInstance().load(PROJECT_PATH + "oldshader.vs", PROJECT_PATH + "oldshader.fs");
    
    init();
    glLinkProgram(this->id);
    initMaterials();
    initLights();
}

// Prepares shader, called each frame
void DeferredPhongShader::prepare(Scene *scene, Camera *camera, Mesh *mesh) {
    
    ShaderProgram::prepare(camera);
    
    GLint uniModel = glGetUniformLocation(this->id, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(mesh->modelMatrix));
    
    glm::mat3 m_normal = glm::inverseTranspose(glm::mat3(camera->view * mesh->modelMatrix));
    
    GLint uniNormMatrix = glGetUniformLocation(this->id, "m_normal");
    glUniformMatrix3fv(uniNormMatrix, 1, GL_FALSE, glm::value_ptr(m_normal));
    
    // upload material for current mesh to gpu
    glBindBuffer(GL_UNIFORM_BUFFER, materialsBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &mesh->material, GL_DYNAMIC_DRAW);
    
    // upload light data to gpu
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    for (std::vector<Light *>::iterator it = scene->lights.begin() ; it != scene->lights.end(); it++) {
        glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &(*it)->data, GL_DYNAMIC_DRAW);
    }
}

// Initializes buffer for material uniform
void DeferredPhongShader::initMaterials() {
    GLuint blockIndex = glGetUniformBlockIndex(id, "Material");
    if(blockIndex == GL_INVALID_INDEX) {
        throw "Invalid uniform block index";
    }
    
    GLuint bindingPoint = DeferredPhongShader::MATERIAL_BINDING_POINT;
    
    glUniformBlockBinding(id, blockIndex, bindingPoint);
    
    glGenBuffers(1, &materialsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, materialsBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, materialsBuffer);
    
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
