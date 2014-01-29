//
//  Mesh.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Mesh__
#define __Excercise_1__Mesh__

#include <iostream>
#include <vector>
#include <memory>
#include <glew.h>

#include "VertexBuffer.h"

class Mesh {
private:
    GLuint verticesBufferId;
    GLuint indicesBufferId;
public:
    std::vector<unsigned int> indices;
    VertexBuffer *vertices;
    Mesh(std::size_t size);
    ~Mesh();
    void load();
    void bind();
};

#endif /* defined(__Excercise_1__Mesh__) */
