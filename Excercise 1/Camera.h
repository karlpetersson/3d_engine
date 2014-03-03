//
//  Camera.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Camera__
#define __Excercise_1__Camera__

#include <iostream>
#include "Object3D.h"
#include <math.h>

class Camera : public Object3D {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    
    glm::mat4 view;
    glm::mat4 projection;
    
    Camera();
    void updateView();
    void useOrthogonalProjection();
    void usePerspectiveProjection();
    void useObliqueProjection();
};

#endif /* defined(__Excercise_1__Camera__) */
