//
//  main.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//
#define GLEW_STATIC

#include <iostream>
#include <fstream>
#include "OFFParser.h"
#include <glew.h>
#include <glfw3.h>
#include "ShaderManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "constants.h"

GLFWwindow* initGl();

float rotationY;
glm::vec3 translation = glm::vec3(0.0,-1.0,-5.0);

void updateProjection(GLFWwindow* window, Camera *camera);

// Takes a window and generates an updated view-matrix based on keys pressed
glm::mat4 updateView(GLFWwindow* window) {
    glm::vec3 velocity;
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationY -= 2.0;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationY += 2.0;
    }
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity.z += cosf(rotationY * M_PI / 180);
        velocity.x -= sinf(rotationY * M_PI / 180);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity.z -= cosf(rotationY * M_PI / 180);
        velocity.x += sinf(rotationY * M_PI / 180);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        velocity.z += sinf(rotationY * M_PI / 180);
        velocity.x += cosf(rotationY * M_PI / 180);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        velocity.z -= sinf(rotationY * M_PI / 180);
        velocity.x -= cosf(rotationY * M_PI / 180);
    }
    
    if(glm::length(velocity) > 0) {
        velocity = glm::normalize(velocity)*0.1f;
        translation += velocity;
    }
    
    return glm::translate(glm::rotate(glm::mat4(1.0), rotationY, glm::vec3(0.0,1.0,0.0)), translation);
}

void updateProjection(GLFWwindow* window, Camera *camera) {
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        camera->usePerspectiveProjection();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        camera->useOrthogonalProjection();
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        camera->useObliqueProjection();
    }
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        camera->useObliqueProjection();
    }
}


int main(int argc, const char * argv[]) {
    
    // init OpenGL
    GLFWwindow* window = initGl();
    
    // Create renderer object
    Renderer renderer = Renderer(window);
    
    // Load object files
    Mesh mesh = OFFParser::parse(PROJECT_PATH + "cooldragon.off");
    Mesh mesh2 = OFFParser::parse(PROJECT_PATH + "cooldragon.off");
    Mesh floor = OFFParser::parse(PROJECT_PATH + "plane.off");
    
    // Create materials for meshes
    Material meshMaterial;
    meshMaterial.ambient = glm::vec4(0.05, 0.1, 0.1, 0.1);
    meshMaterial.diffuse = glm::vec4(0.1, 0.5, 0.5, 0.5);
    meshMaterial.specular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    meshMaterial.shininess = 70.0;
    
    Material meshMaterial2;
    meshMaterial2.ambient = glm::vec4(0.1, 0.05, 0.05, 1.0);
    meshMaterial2.diffuse = glm::vec4(0.7, 0.3, 0.3, 1.0);
    meshMaterial2.specular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    meshMaterial2.shininess = 150.0;
    
    Material floorMaterial;
    floorMaterial.ambient = glm::vec4(0.1, 0.1, 0.1, 1.0);
    floorMaterial.diffuse = glm::vec4(0.4, 0.4, 0.4, 1.0);
    floorMaterial.specular = glm::vec4(0.0, 0.0, 0.0, 1.0);
    floorMaterial.shininess = 15.0;

    // load meshes with materials
    mesh.load(meshMaterial);
    mesh2.load(meshMaterial2);
    
    mesh.translate(glm::vec3(0.0f ,0.5f, 0.0f));
    mesh2.translate(glm::vec3(2.0f ,0.5f, 0.0f));
    
    // load floormesh
    floor.load(floorMaterial);
    floor.translate(glm::vec3(0.0f ,-0.1f, 0.0f));
    floor.rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f);
    floor.scale(glm::vec3(10.0f ,10.0, 1.0f));
    
    // Create scene and camera
    Scene scene = Scene();
    Camera camera = Camera();
    
    // create one light
    Light light = Light(glm::vec4(0.0f, 4.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light.translate(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
    // Add meshes, light and floor to the scene
    scene.add(&mesh);
    scene.add(&mesh2);
    scene.add(&light);
    scene.add(&floor);

    while(!glfwWindowShouldClose(window))
    {
        // Update the cameras view matrix each frame
        camera.view = updateView(window);
        updateProjection(window, &camera);
        
        mesh2.rotate(glm::vec3(0.0f, 0.5f, 0.0f), 1.0f);

        // render frame
        renderer.render(&scene, &camera);
    }
    
    glfwTerminate();
    
    return 0;
}

GLFWwindow* initGl() {
    if(!glfwInit()) {
        std::cerr << "could not initialize glfw" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if(!window) {
        std::cerr << "could not create glfw window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_ONE);
    
    return window;
}
