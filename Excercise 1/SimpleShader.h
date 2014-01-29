//
//  SimpleShader.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__SimpleShader__
#define __Excercise_1__SimpleShader__

#include <iostream>
#include "ShaderProgram.h"

class SimpleShader : public ShaderProgram {
private:
    GLuint vao;
public:
    SimpleShader();
    void use();
    GLuint getId();
};

#endif /* defined(__Excercise_1__SimpleShader__) */
