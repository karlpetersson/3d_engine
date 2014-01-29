//
//  SimpleShader.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "SimpleShader.h"

SimpleShader::SimpleShader() {
    this->id = ShaderManager::getInstance().load("/Users/karlpetersson/Workspace/Excercise 1/Excercise 1/shader.vertsh", "/Users/karlpetersson/Workspace/Excercise 1/Excercise 1/shader.fragsh");
    
    glBindFragDataLocation(this->id, 0, "outColor");
    glLinkProgram(this->id);
    
    GLint posAttrib = glGetAttribLocation(this->id, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(posAttrib);
}

void SimpleShader::use() {
    glUseProgram(this->id);
}

GLuint SimpleShader::getId() {
    return this->id;
}