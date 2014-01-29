//
//  Mesh.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh(std::size_t size) {
    this->vertices = new VertexBuffer(size);
}

void Mesh::load() {
    glGenBuffers(1, &this->verticesBufferId);
    glGenBuffers(1, &this->indicesBufferId);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBufferId);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (this->vertices->size*sizeof(Vertex)), this->vertices->buffer, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr) (this->indices.size()*sizeof(GL_UNSIGNED_INT)),
                 &this->indices[0], GL_STATIC_DRAW);
    
}

void Mesh::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBufferId);
}

Mesh::~Mesh() {
    
}