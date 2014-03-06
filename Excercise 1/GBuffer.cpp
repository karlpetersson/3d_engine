//
//  FBORenderTexture.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "GBuffer.h"

bool GBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
    
    this->width = WindowWidth;
    this->height = WindowHeight;
    
    // Create the FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    
    // Create the gbuffer textures
   // glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);
    
    for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES - 1 ; i++) {
        glGenTextures(1, &m_textures[i]);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
        glBindTexture(GL_TEXTURE_2D, 0);
        
        // attach to fbo?
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
        
    }
    
    glGenTextures(1, &m_textures[GBUFFER_TEXTURE_TYPE_DEPTH]);
    
    // depth
    glActiveTexture(GL_TEXTURE0 + GBUFFER_TEXTURE_TYPE_DEPTH);
    glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_DEPTH]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_DEPTH], 0);

    // drawbuffers

    int numberOfDrawBuffers = GBUFFER_NUM_TEXTURES;
    GLuint drawBuffers[numberOfDrawBuffers];
    for(int i = 0; i < numberOfDrawBuffers; i++) {
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    
    glDrawBuffers(numberOfDrawBuffers, &drawBuffers[0]);
    
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        exit(EXIT_FAILURE);
    }
    
    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    return true;
}

GLuint GBuffer::getTexture(unsigned int n) {
    return m_textures[n];
}

GLuint GBuffer::getDepthTexture() {
    return m_depthTexture;
}

void GBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void GBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::BindTexture(unsigned int n)
{
    glActiveTexture(GL_TEXTURE0 + n);
    glBindTexture(GL_TEXTURE_2D, m_textures[n]);
}

void GBuffer::unbindTexture(unsigned int n) {
    glActiveTexture(GL_TEXTURE0 + n);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GBuffer::blit(GLuint target, int targetWidth, int targetHeight) {
    
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target);
    glBlitFramebuffer(0,0,width, height, 0,0,targetWidth, targetHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::initTexture(int width, int height, int texIndex) {
    
}