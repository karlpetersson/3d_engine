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
#include <gtkmm.h>
#include "GUIController.h"
#include <thread>


GLFWwindow* initGl();

bool shouldLoadFile;
std::string fileNameToLoad;

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

int displayGui(int argc, char *argv[], Camera *camera, Light *light, Material *material, bool *flipNormals, bool *shouldLoadNewFile, std::string *filename) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    GUIController *gui = new GUIController(camera, light, material, flipNormals, shouldLoadNewFile, filename);
    return app->run(*gui);
}


int main(int argc, char * argv[]) {
    
    // init OpenGL
    GLFWwindow* window = initGl();
    
    // Create renderer object
    Renderer renderer = Renderer(window);
    
    // Load object files
    Mesh mesh = OFFParser::parse(PROJECT_PATH + "cooldragon.off");
    Mesh mesh2 = OFFParser::parse(PROJECT_PATH + "cooldragon.off");
    Mesh floor = OFFParser::parse(PROJECT_PATH + "plane.off");

    // Create materials for meshes
    /*Material meshMaterial;
    meshMaterial.ambient = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
    meshMaterial.diffuse = glm::vec4(0.5f, 0.5f, 0.7f, 1.0f);
    meshMaterial.specular = glm::vec4(0.6f, 0.6f, 0.7f, 1.0f);
    meshMaterial.shininess = 250.0f;
    
    Material meshMaterial2;
    meshMaterial2.ambient = glm::vec4(0.1, 0.05, 0.05, 1.0);
    meshMaterial2.diffuse = glm::vec4(0.7, 0.3, 0.3, 1.0);
    meshMaterial2.specular = glm::vec4(0.8, 0.8, 0.8, 1.0);
    meshMaterial2.shininess = 150.0;*/
    
    Material meshMaterial;
    meshMaterial.ambient = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
    meshMaterial.diffuse = glm::vec4(0.9f, 0.8f, 0.8f, 1.0f);
    meshMaterial.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    meshMaterial.shininess = 250.0f;
    
    Material floorMaterial;
    floorMaterial.ambient = glm::vec4(0.1, 0.1, 0.1, 1.0);
    floorMaterial.diffuse = glm::vec4(0.6, 0.6, 0.6, 1.0);
    floorMaterial.specular = glm::vec4(0.0, 0.0, 0.0, 1.0);
    floorMaterial.shininess = 5.0f;

    // load meshes with materials
    mesh.load(meshMaterial);
    mesh2.load(meshMaterial);
    
    mesh.translate(glm::vec3(0.0f ,0.5f, 0.0f));
    mesh2.translate(glm::vec3(2.0f ,0.5f, 0.0f));
    
    // load floormesh
    floor.load(floorMaterial);
    floor.translate(glm::vec3(0.0f ,-0.1f, 0.0f));
    floor.rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f);
    floor.scale(glm::vec3(10.0f ,10.0, 1.0f));
    
    // Create scene and camera
    Scene scene = Scene();
    Camera camera = Camera(window, 60.0f, 800.0f/600.0f, 0.1f, 1000.0f);
    
    // create one light
    Light light = Light(glm::vec4(0.0f, 4.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light.translate(glm::vec4(3.0f, 0.0f, 0.0f, 1.0f));

    Light light2 = Light(glm::vec4(0.0f, 4.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    light2.translate(glm::vec4(-3.0f, 0.0f, 1.0f, 1.0f));
    
    Light light3 = Light(glm::vec4(0.0f, 4.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.7f, 0.7f, 1.0f));
    light3.translate(glm::vec4(0.0f, 0.0f, 3.0f, 1.0f));
    
    // Add meshes, light and floor to the scene
    scene.add(&mesh);
    scene.add(&mesh2);
    scene.add(&light);
    scene.add(&light2);
    scene.add(&light3);
    scene.add(&floor);
    
    std::thread thr = std::thread(displayGui, argc, argv, &camera, &light, &mesh2.material, &mesh2.flipNormals, &shouldLoadFile, &fileNameToLoad);

    while(!glfwWindowShouldClose(window))
    {
        
        if(shouldLoadFile) {
            mesh2 = OFFParser::parse(PROJECT_PATH + fileNameToLoad);
            mesh2.load(meshMaterial);
            mesh2.translate(glm::vec3(2.0f ,0.5f, 0.0f));
            shouldLoadFile = false;
        }
        
        // Update the cameras view matrix each frame
        //camera.view = updateView(window);
        camera.update();
        //camera.updateMovementBezier();
        updateProjection(window, &camera);
        
        mesh2.rotate(glm::vec3(0.0f, 0.5f, 0.0f), 1.0f);

        // render frame
        renderer.render(&scene, &camera);
    }
    
    glfwTerminate();
    
    thr.join();
    
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
    
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    return window;
}
