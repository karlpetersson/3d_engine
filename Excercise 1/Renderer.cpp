//
//  Renderer.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window) {
    this->window = window;
    this->shader = std::shared_ptr<PhongShader>(new PhongShader());
}

Renderer::~Renderer() {
}

// Renders a scene
void Renderer::render(Scene *scene, Camera *camera) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // use the current shader
    this->shader->use();
    
    // for each mesh registered to the scene
    for (std::vector<Mesh *>::iterator it = scene->objects.begin() ; it != scene->objects.end(); it++) {
        
        // let shader upload data for that mesh
        this->shader->prepare(scene, camera, *it);
        
        // render mesh
        (*it)->bind();
        (*it)->render(scene);
        (*it)->unbind();
    }
    
    // render frame by swapping buffers
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

bool Renderer::hasWindowOpen() {
    return !glfwWindowShouldClose(this->window);
}