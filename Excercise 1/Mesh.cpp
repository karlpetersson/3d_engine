//
//  Mesh.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh(std::size_t size) {
    Object3D::Object3D();
    this->vertices = new VertexBuffer(size);
}

// creates and binds buffers for vertices and indices
void Mesh::load(Material m) {
    
    this->material = m;
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->verticesBufferId);
    glGenBuffers(1, &this->indicesBufferId);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBufferId);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (this->vertices->size*sizeof(Vertex)), this->vertices->buffer, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr) (this->indices.size()*sizeof(GL_UNSIGNED_INT)),
                 &this->indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(ATTRIB_POS);
    glVertexAttribPointer(ATTRIB_POS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    glEnableVertexAttribArray(ATTRIB_NORM);
    glVertexAttribPointer(ATTRIB_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(Vec3));

    glBindVertexArray(0);

}

void Mesh::bind() {
    glBindVertexArray(this->vao);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

void Mesh::render(Scene *scene) {
    bind();
    glDrawElements(GL_TRIANGLES, (GLsizei) this->indices.size(), GL_UNSIGNED_INT, NULL);
    unbind();
}

Mesh::~Mesh() {
    
}