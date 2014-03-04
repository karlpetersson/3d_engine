//
//  PhongShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-02.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "PhongShader.h"

PhongShader::PhongShader() {
    this->id = ShaderManager::getInstance().load(PROJECT_PATH + "geometryPass.vs", PROJECT_PATH + "geometryPass.fs");
    
    init();
    glLinkProgram(this->id);
    initMaterials();
    initLights();
}

// Prepares shader, called each frame
void PhongShader::prepare(Scene *scene, Camera *camera, Mesh *mesh) {
    
    ShaderProgram::prepare(camera, mesh);
    
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
void PhongShader::initMaterials() {
    GLuint blockIndex = glGetUniformBlockIndex(id, "Material");
    if(blockIndex == GL_INVALID_INDEX) {
        throw "Invalid uniform block index";
    }
    
    GLuint bindingPoint = PhongShader::MATERIAL_BINDING_POINT;
    
    glUniformBlockBinding(id, blockIndex, bindingPoint);
    
    glGenBuffers(1, &materialsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, materialsBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, materialsBuffer);
   
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
