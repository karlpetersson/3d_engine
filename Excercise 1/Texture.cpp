//
//  Texture.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-06.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Texture.h"

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, t_id);
}

void Texture::unbind() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
}