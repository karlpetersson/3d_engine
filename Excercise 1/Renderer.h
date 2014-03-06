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
#include "PhongShader.h"
#include "GeometryShader.h"
#include "DeferredPhongShader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Mesh.h"
#include "Camera.h"
#include "GBuffer.h"

class Scene;

class Renderer {
private:
    GLFWwindow* window;
    std::shared_ptr<PhongShader> lightingShader;
    std::shared_ptr<GeometryShader> geometryShader;
    std::shared_ptr<DeferredPhongShader> oldShader;
public:
    GBuffer *m_gbuffer;
    Mesh *quad;
    
    Renderer(GLFWwindow* window);
    ~Renderer();
    void render(Scene *scene, Camera *camera);
    void geometryPass(Scene *scene, Camera *camera);
    void lightingPass(Scene *scene, Camera *camera);
    void forwardRender(Scene *scene, Camera*camera);
    bool hasWindowOpen();
};

#endif /* defined(__Excercise_1__Renderer__) */
