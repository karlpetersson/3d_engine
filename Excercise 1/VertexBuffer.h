//
//  VertexBuffer.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-22.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__VertexBuffer__
#define __Excercise_1__VertexBuffer__

#include <iostream>

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Color {
    float r;
    float g;
    float b;
};

struct Vertex {
    Vec3 pos;
    Vec3 norm;
    Color color;
};

class VertexBuffer {
public:
    size_t size;
    VertexBuffer(std::size_t size);
    Vertex *buffer;
};

#endif /* defined(__Excercise_1__VertexBuffer__) */
