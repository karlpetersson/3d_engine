//
//  DepthTexture.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-06.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "DepthTexture.h"

void DepthTexture::init(int width, int height, TEXTURE_TYPE type) {
    this->width = width;
    this->height = height;
    this->index = type;
    
    glGenTextures(1, &t_id);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, t_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
