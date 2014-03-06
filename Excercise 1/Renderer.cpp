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
    this->oldShader = std::shared_ptr<DeferredPhongShader>(new DeferredPhongShader());
    
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    this->m_gbuffer = new GBuffer();
    m_gbuffer->Init(width, height);
}

Renderer::~Renderer() {
}

// Renders a scene
void Renderer::render(Scene *scene, Camera *camera) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

     geometryPass(scene, camera);
     lightingPass(scene, camera);
    // forwardRender(scene, camera);
    
    //int width;
    //int height;
    //glfwGetFramebufferSize(window, &width, &height);
    
    // blit framebuffer to standard buffer
    
   //  m_gbuffer->blit(0, width, height);
    
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
    
    glDepthMask(GL_TRUE);

    m_gbuffer->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
    //glDisable (GL_DEPTH_TEST);

    m_gbuffer->unbind();

    //glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT);

    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_AMBIENT);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_SHININESS);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_DEPTH);
    
    this->lightingShader->use();
    this->lightingShader->prepare(scene, camera);

    quad->render(scene);
    
    //m_gbuffer->unbind();
    
    glDepthMask(GL_TRUE);
    glDisable (GL_BLEND);
    
    /*m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_AMBIENT);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_SHININESS);
    m_gbuffer->BindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_DEPTH);*/
    
    //m_gbuffer->unbind();

}

bool Renderer::hasWindowOpen() {
    return !glfwWindowShouldClose(this->window);
}