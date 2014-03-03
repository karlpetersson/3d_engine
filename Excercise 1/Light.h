//
//  Light.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Light__
#define __Excercise_1__Light__

#include <iostream>
#include "Object3D.h"

struct LightData {
    glm::vec4 l_pos;
    glm::vec4 l_color;
};

class Light : public Object3D {
public:
    LightData data;
    Light(glm::vec4 pos, glm::vec4 color);
    void translate(glm::vec4 vec);
};

#endif /* defined(__Excercise_1__Light__) */
