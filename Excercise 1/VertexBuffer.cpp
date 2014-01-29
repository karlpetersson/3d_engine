//
//  VertexBuffer.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-22.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::size_t size) {
    this->size = size;
    this->buffer = new Vertex[size];
}