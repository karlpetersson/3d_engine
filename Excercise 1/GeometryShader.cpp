//
//  GeometryShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-04.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "GeometryShader.h"

GeometryShader::GeometryShader() {
    this->id = ShaderManager::getInstance().load(PROJECT_PATH + "geometry.vs", PROJECT_PATH + "geometry.fs");
    
    init();
    
    glBindFragDataLocation(this->id, TEXTURE_TYPE_NORMAL, "outNormal");
    glBindFragDataLocation(this->id, TEXTURE_TYPE_DIFFUSE, "outDiffuse");
    glBindFragDataLocation(this->id, TEXTURE_TYPE_AMBIENT, "outAmbient");
    glBindFragDataLocation(this->id, TEXTURE_TYPE_SPECULAR, "outSpecular");
    glBindFragDataLocation(this->id, TEXTURE_TYPE_SHININESS, "outShininess");
    
    glLinkProgram(this->id);
    initMaterials();
}

// Prepares shader, called each frame
void GeometryShader::prepare(Scene *scene, Camera *camera, Mesh *mesh) {
    
    ShaderProgram::prepare(camera);
    
    GLint uniModel = glGetUniformLocation(this->id, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(mesh->modelMatrix));
    
    glm::mat3 m_normal = glm::inverseTranspose(glm::mat3(camera->view * mesh->modelMatrix));
    
    GLint uniNormMatrix = glGetUniformLocation(this->id, "m_normal");
    glUniformMatrix3fv(uniNormMatrix, 1, GL_FALSE, glm::value_ptr(m_normal));
    
    // upload material for current mesh to gpu
    glBindBuffer(GL_UNIFORM_BUFFER, materialsBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &mesh->material, GL_DYNAMIC_DRAW);
    
}

// Initializes buffer for material uniform
void GeometryShader::initMaterials() {
    GLuint blockIndex = glGetUniformBlockIndex(id, "Material");
    if(blockIndex == GL_INVALID_INDEX) {
        throw "Invalid uniform block index";
    }
    
    GLuint bindingPoint = GeometryShader::MATERIAL_BINDING_POINT;
    
    glUniformBlockBinding(id, blockIndex, bindingPoint);
    
    glGenBuffers(1, &materialsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, materialsBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, materialsBuffer);
    
}