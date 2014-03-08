//
//  Texture.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-06.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Texture__
#define __Excercise_1__Texture__

#include <iostream>
#include "constants.h"
#include <glew.h>

class Texture {
public:
    
    TEXTURE_TYPE index;
    unsigned int t_id;
    int width;
    int height;
        
    virtual void init(int width, int height, TEXTURE_TYPE type){};
    void bind();
    void unbind();

};

#endif /* defined(__Excercise_1__Texture__) */
