//
//  constants.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include <string>

#ifndef Excercise_1_constants_h
#define Excercise_1_constants_h

#define ATTRIB_POS 0
#define ATTRIB_NORM 1

#ifdef __APPLE__
static const std::string PROJECT_PATH = "/Users/karlpetersson/Workspace/Excercise 1/Excercise 1/";
#else
static const std::string PROJECT_PATH = "./";
#endif

enum TEXTURE_TYPE {
    TEXTURE_TYPE_NORMAL,
    TEXTURE_TYPE_DIFFUSE,
    TEXTURE_TYPE_AMBIENT,
    TEXTURE_TYPE_SPECULAR,
    TEXTURE_TYPE_SHININESS,
    TEXTURE_TYPE_DEPTH,
    NUM_TEXTURES
};

#endif
