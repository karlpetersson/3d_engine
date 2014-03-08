//
//  ColorTexture.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-06.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__ColorTexture__
#define __Excercise_1__ColorTexture__

#include <iostream>
#include "Texture.h"

class ColorTexture : public Texture{
public:
    void init(int width, int height, TEXTURE_TYPE type);
};

#endif /* defined(__Excercise_1__ColorTexture__) */
