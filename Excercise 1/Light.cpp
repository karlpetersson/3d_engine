//
//  Light.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Light.h"

Light::Light(glm::vec4 pos, glm::vec4 color) {
    Object3D::Object3D();
    data.l_pos = pos;
    data.l_color = color;
}

void Light::translate(glm::vec4 vec) {
    
    data.l_pos = glm::vec4(data.l_pos.x, data.l_pos.y, data.l_pos.z, 0.0) + vec;
    
    /*data.l_pos.x = data.l_pos.x + vec.x;
    data.l_pos.y = data.l_pos.y + vec.y;
    data.l_pos.z = data.l_pos.z + vec.z;*/
}