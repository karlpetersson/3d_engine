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
#include "Mesh.h"
#include "OFFParser.h"
#include <thread>
#include <glew.h>
#include <glfw3.h>
#include "ShaderManager.h"
#include "SimpleShader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


int main(int argc, const char * argv[]) {
    
    std::ifstream file;
    file.open("/Users/karlpetersson/Workspace/Excercise 1/Excercise 1/space_station.off");
    if(!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    Mesh mesh = OFFParser::parse(&file);
    file.close();
    
    if(!glfwInit()) {
        std::cerr << "could not initialize glfw" << std::endl;
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 //   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL); // Windowed
    if(!window) {
        std::cerr << "could not create glfw window" << std::endl;
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    mesh.load();
    SimpleShader shader = SimpleShader();
    //mesh.bind();
    shader.use();
    
    GLint uniModel = glGetUniformLocation(shader.getId(), "model");


    // Set up projection
    glm::mat4 view = glm::mat4(1.);
    view = glm::translate(view, glm::vec3(0.0f,0.0f, -40.0f));
    
    GLint uniView = glGetUniformLocation(shader.getId(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    
    glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    GLint uniProj = glGetUniformLocation(shader.getId(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 model = glm::mat4(1.);
        model = glm::rotate(model,
                            (GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 360.0f * 5.0f,
                            glm::vec3(0.5f, 0.5f, 0.5f)
                            );
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        
        glDrawElements(GL_TRIANGLES, (GLsizei) mesh.indices.size(), GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

