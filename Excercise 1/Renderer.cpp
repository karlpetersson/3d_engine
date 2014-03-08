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
    this->lightingShader = std::shared_ptr<DeferredPhongShader>(new DeferredPhongShader());
    this->geometryShader = std::shared_ptr<GeometryShader>(new GeometryShader());
    this->oldShader = std::shared_ptr<PhongShader>(new PhongShader());
    
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    
    this->m_gbuffer = new GBuffer();
    m_gbuffer->init(width, height);
}

Renderer::~Renderer() {
}

// Renders a scene
void Renderer::render(Scene *scene, Camera *camera) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

     geometryPass(scene, camera);
     lightingPass(scene, camera);
    // forwardRender(scene, camera);
    
    // render frame by swapping buffers
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Renderer::forwardRender(Scene *scene, Camera*camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // use the current shader
    this->oldShader->use();
    
    // for each mesh registered to the scene
    for (std::vector<Mesh *>::iterator it = scene->objects.begin() ; it != scene->objects.end(); it++) {
        
        // let shader upload data for that mesh
        this->oldShader->prepare(scene, camera, *it);
        
        (*it)->render(scene);
    }
}

void Renderer::geometryPass(Scene *scene, Camera *camera) {
    
    m_gbuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_TRUE);

    // use the current shader
    this->geometryShader->use();
    
    // for each mesh registered to the scene
    for (std::vector<Mesh *>::iterator it = scene->objects.begin() ; it != scene->objects.end(); it++) {
        
        // let shader upload data for that mesh
        this->geometryShader->prepare(scene, camera, *it);
        
        (*it)->render(scene);
    }
    
    m_gbuffer->unbind();
}

void Renderer::lightingPass(Scene *scene, Camera *camera) {
    
    
    glDepthMask(GL_FALSE);
    glEnable (GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE); // additive

    m_gbuffer->unbind();

    glClear(GL_COLOR_BUFFER_BIT);

    m_gbuffer->bindTextures();
    
    this->lightingShader->use();
    this->lightingShader->prepare(scene, camera);

    quad->render(scene);
    
    glDepthMask(GL_TRUE);
    glDisable (GL_BLEND);

}

bool Renderer::hasWindowOpen() {
    return !glfwWindowShouldClose(this->window);
}