//
//  FBORenderTexture.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "GBuffer.h"

bool GBuffer::init(unsigned int WindowWidth, unsigned int WindowHeight)
{
    
    this->width = WindowWidth;
    this->height = WindowHeight;
    
    glGenFramebuffers(1, &m_fbo);

    std::shared_ptr<DepthTexture> depthTexture(new DepthTexture);
    depthTexture->init(width, height, TEXTURE_TYPE_DEPTH);
    setDepthTexture(depthTexture);

    std::shared_ptr<ColorTexture> normalTexture(new ColorTexture);
    normalTexture->init(width, height, TEXTURE_TYPE_NORMAL);
    addColorTexture(normalTexture);
    
    std::shared_ptr<ColorTexture> diffuseTexture(new ColorTexture);
    diffuseTexture->init(width, height, TEXTURE_TYPE_DIFFUSE);
    addColorTexture(diffuseTexture);
    
    std::shared_ptr<ColorTexture> ambientTexture(new ColorTexture);
    ambientTexture->init(width, height, TEXTURE_TYPE_AMBIENT);
    addColorTexture(ambientTexture);
    
    std::shared_ptr<ColorTexture> specularTexture(new ColorTexture);
    specularTexture->init(width, height, TEXTURE_TYPE_SPECULAR);
    addColorTexture(specularTexture);
    
    std::shared_ptr<ColorTexture> shininessTexture(new ColorTexture);
    shininessTexture->init(width, height, TEXTURE_TYPE_SHININESS);
    addColorTexture(shininessTexture);
    
    // check status of fbo
    bind();
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "frame buffer error, status: 0x%x\n", Status);
        exit(EXIT_FAILURE);
    }
    unbind();
    
    return true;
}

// binds the fbo
void GBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

// unbinds the fbo (binds to the standard framebuffer, 0)
void GBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::blit(GLuint target, int targetWidth, int targetHeight) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target);
    glBlitFramebuffer(0,0,width, height, 0,0,targetWidth, targetHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

// binds a color texture to the fbo and calls updateColorBuffers
void GBuffer::addColorTexture(std::shared_ptr<ColorTexture> colorTexture) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorTexture->index, GL_TEXTURE_2D, colorTexture->t_id, 0);
    colorTextures.push_back(colorTexture);
    updateColorBuffers();
    unbind();
}

// binds a depth texture to the fbo
void GBuffer::setDepthTexture(std::shared_ptr<DepthTexture> depthTexture) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture->t_id, 0);
    this->depthTexture = depthTexture;
    unbind();
}

// updates color buffers
void GBuffer::updateColorBuffers() {
    GLuint c_buffers[NUM_TEXTURES];
    for(int i = 0; i < NUM_TEXTURES; i++) {
        c_buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers(NUM_TEXTURES, &c_buffers[0]);
    
}

// Binds all attached color textures
void GBuffer::bindTextures() {
    std::vector<std::shared_ptr<ColorTexture>>::iterator it;
    for(it = colorTextures.begin(); it != colorTextures.end(); it++) {
        (*it)->bind();
    }
    depthTexture->bind();
}