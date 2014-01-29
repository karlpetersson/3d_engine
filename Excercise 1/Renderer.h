//
//  Renderer.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Renderer__
#define __Excercise_1__Renderer__

#include <iostream>
#include <glew.h>
#include <glfw3.h>

class Renderer {
private:
    GLFWwindow* window;
public:
    Renderer();
    void Render();
};

#endif /* defined(__Excercise_1__Renderer__) */
