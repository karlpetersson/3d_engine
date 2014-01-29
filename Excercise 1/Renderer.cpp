//
//  Renderer.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    this->window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL); // Windowed
    if(!this->window) {
        std::cerr << "could not create glfw window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
        //handle err
    }
    
    glfwMakeContextCurrent(this->window);
}