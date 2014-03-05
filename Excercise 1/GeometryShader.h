//
//  GeometryShader.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-04.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__GeometryShader__
#define __Excercise_1__GeometryShader__

#include <iostream>
#include "ShaderProgram.h"
#include <vector>

class GeometryShader : public ShaderProgram {
private:
    GLuint materialsBuffer;
    void initMaterials();
public:
    enum {
        MATERIAL_BINDING_POINT = 2,
        LIGHT_BINDING_POINT = 3
    };
    GeometryShader();
    void prepare(Scene *scene, Camera *camera, Mesh *mesh);
};



#endif /* defined(__Excercise_1__GeometryShader__) */
