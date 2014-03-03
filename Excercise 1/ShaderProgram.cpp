//
//  ShaderProgram.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "ShaderProgram.h"

void ShaderProgram::init() {
    glBindFragDataLocation(this->id, 0, "outColor");
    glBindAttribLocation(this->id, ATTRIB_POS, "position");
    glBindAttribLocation(this->id, ATTRIB_NORM, "normal");
}

// uploads matrices to gpu
void ShaderProgram::prepare(Camera *camera, Mesh *mesh) {
    GLint uniView = glGetUniformLocation(this->id, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera->view));
    
    GLint uniProj = glGetUniformLocation(this->id, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(camera->projection));
    
    GLint uniModel = glGetUniformLocation(this->id, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(mesh->modelMatrix));
    
    glm::mat3 m_normal = glm::inverseTranspose(glm::mat3(camera->view * mesh->modelMatrix));
    
    GLint uniNormMatrix = glGetUniformLocation(this->id, "m_normal");
    glUniformMatrix3fv(uniNormMatrix, 1, GL_FALSE, glm::value_ptr(m_normal));
}

void ShaderProgram::use() {
    glUseProgram(this->id);
}

GLuint ShaderProgram::getId() {
    return this->id;
}