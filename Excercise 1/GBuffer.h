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
    
    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TEXTURE_TYPE_NORMAL,
        GBUFFER_TEXTURE_TYPE_DIFFUSE,
        GBUFFER_TEXTURE_TYPE_AMBIENT,
        GBUFFER_TEXTURE_TYPE_SPECULAR,
        GBUFFER_TEXTURE_TYPE_SHININESS,
        GBUFFER_TEXTURE_TYPE_DEPTH,
        GBUFFER_NUM_TEXTURES
    };
    
    GLuint m_textures[GBUFFER_NUM_TEXTURES];
    GLuint m_depthTexture;
    
    GBuffer() {};
    ~GBuffer() {};
    
    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
    GLuint getTexture(unsigned int n);
    GLuint getDepthTexture();
    void Bind();
    void unbind();
    void BindTexture(unsigned int n);
    void unbindTexture(unsigned int n);
    void initTexture(int width, int height, int texIndex);
    void blit(GLuint target, int targetWidth, int targetHeight);


private:
    int width;
    int height;
    
    //std::vector<std::shared_ptr<ColorTexture>> colorTextures;
   // std::shared_ptr<DepthTexture> depthTexture;

    
    GLuint m_fbo;
};

#endif /* defined(__Excercise_1__GBuffer__) */
