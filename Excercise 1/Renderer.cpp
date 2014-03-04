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
    this->lightingShader = std::shared_ptr<PhongShader>(new PhongShader());
    this->geometryShader = std::shared_ptr<GeometryShader>(new GeometryShader());
    
    int *width = nullptr;
    int *height = nullptr;
    glfwGetWindowSize(window, width, height);
    if(width == nullptr || height == nullptr) {
        std::cerr << "coudlnt get window width/height" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->m_gbuffer = new GBuffer();
    m_gbuffer->Init(*width, *height);
}

Renderer::~Renderer() {
}

// Renders a scene
void Renderer::render(Scene *scene, Camera *camera) {

    geometryPass(scene, camera);
    // lightingPass(scene, camera);
    
    // render frame by swapping buffers
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Renderer::geometryPass(Scene *scene, Camera *camera) {
    
    m_gbuffer->BindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the current shader
    this->geometryShader->use();
    
    // for each mesh registered to the scene
    for (std::vector<Mesh *>::iterator it = scene->objects.begin() ; it != scene->objects.end(); it++) {
        
        // let shader upload data for that mesh
        this->geometryShader->prepare(scene, camera, *it);
        
        // render mesh into each texture
        for (unsigned int i = 0 ; i < GBuffer::GBUFFER_NUM_TEXTURES ; i++) {
            
            m_gbuffer->BindTexture(i);
            
            (*it)->bind();
            (*it)->render(scene);
            (*it)->unbind();
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Renderer::lightingPass(Scene *scene, Camera *camera) {
    m_gbuffer->BindForReading();
    
    glClearColor (0.2, 0.2, 0.2, 0.0f); // added ambient light here
    glClear (GL_COLOR_BUFFER_BIT);
    
    glEnable (GL_BLEND);
    glBlendEquation (GL_FUNC_ADD);
    glBlendFunc (GL_ONE, GL_ONE); // additive
    
    glDisable (GL_DEPTH_TEST);
    glDepthMask (GL_FALSE);
    
    glActiveTexture(GL_TEXTURE0);
    m_gbuffer->BindTexture(0);
    glActiveTexture(GL_TEXTURE1);
    m_gbuffer->BindTexture(1);
    glActiveTexture(GL_TEXTURE2);
    m_gbuffer->BindTexture(2);
    glActiveTexture(GL_TEXTURE3);
    m_gbuffer->BindTexture(3);
    glActiveTexture(GL_TEXTURE4);
    m_gbuffer->BindTexture(4);
    glActiveTexture(GL_TEXTURE5);
    m_gbuffer->BindTexture(5);
    
    this->lightingShader->use();
    //this->lightingShader->prepare(scene, camera, mesh);
    
    glEnable (GL_DEPTH_TEST);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);

}

bool Renderer::hasWindowOpen() {
    return !glfwWindowShouldClose(this->window);
}