//
//  FBORenderTexture.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__GBuffer__
#define __Excercise_1__GBuffer__

#include <iostream>

#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "ColorTexture.h"
#include "DepthTexture.h"

class GBuffer {
public:
    
    GBuffer() {};
    ~GBuffer() {};
    
    bool init(unsigned int WindowWidth, unsigned int WindowHeight);
    
    void bind();
    void unbind();
    
    void bindTextures();
    void addColorTexture(std::shared_ptr<ColorTexture> colorTexture);
    void setDepthTexture(std::shared_ptr<DepthTexture> depthTexture);
    void updateColorBuffers();
    void blit(GLuint target, int targetWidth, int targetHeight);

private:
    int width;
    int height;
    
    std::vector<std::shared_ptr<ColorTexture>> colorTextures;
    std::shared_ptr<DepthTexture> depthTexture;

    GLuint m_fbo;
};

#endif /* defined(__Excercise_1__GBuffer__) */
