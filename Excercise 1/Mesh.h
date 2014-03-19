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
#include "Object3D.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "constants.h"

struct Material {
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
};

class Mesh : public Object3D{
private:    
    GLuint verticesBufferId;
    GLuint indicesBufferId;
    GLuint vao;
public:
    Material material;
    bool flipNormals;
    
    std::vector<unsigned int> indices;
    VertexBuffer *vertices;
    Mesh(std::size_t size);
    ~Mesh();
    void load(Material m);
    void bind();
    void unbind();
    void render(Scene *scene);
};


#endif /* defined(__Excercise_1__Mesh__) */
