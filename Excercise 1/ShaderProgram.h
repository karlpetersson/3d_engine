//
//  ShaderProgram.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__ShaderProgram__
#define __Excercise_1__ShaderProgram__

#include <iostream>
#include "ShaderManager.h"
#include "VertexBuffer.h"

class ShaderProgram {
protected:
    int id;
public:
    ShaderProgram() {};
    virtual void use() {};
};

#endif /* defined(__Excercise_1__ShaderProgram__) */
