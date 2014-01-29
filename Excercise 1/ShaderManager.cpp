//
//  ShaderManager.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "ShaderManager.h"

GLuint ShaderManager::load(std::string vertexShader, std::string fragmentShader) {
    
    GLuint vertexShaderId = this->loadVertexShader(vertexShader);
    GLuint fragmentShaderId = this->loadFragmentShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
        
    return shaderProgram;
    
}

GLuint ShaderManager::loadVertexShader(std::string source) {
    
    std::map<std::string, GLuint>::const_iterator it;
    it = this->vertexShaders.find(source);
    if(it != vertexShaders.end())
    {
        return it->second;
    }
    
    std::string vertexSourceString = this->parseSourceFile(source);
    
    GLchar const *vertexSource = vertexSourceString.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    
    // compile shader
    glCompileShader(vertexShader);
    
    // test shader
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(!status) {
        std::cerr << "could not compile vertex shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    vertexShaders[source] = vertexShader;
    return vertexShader;
}

GLuint ShaderManager::loadFragmentShader(std::string source) {
    
    std::map<std::string, GLuint>::const_iterator it;
    it = this->fragmentShaders.find(source);
    if(it != fragmentShaders.end())
    {
        return it->second;
    }
    
    std::string fragmentSourceString = this->parseSourceFile(source);
    
    GLchar const *fragmentSource = fragmentSourceString.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    
    // compile shader
    glCompileShader(fragmentShader);
    
    // test shader
    GLint status;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(!status) {
        std::cerr << "could not compile vertex shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    fragmentShaders[source] = fragmentShader;
    return fragmentShader;
    
}

std::string ShaderManager::parseSourceFile(std::string filename) {
    
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        std::cerr << "Could not open shader source-file" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::string sourceString( (std::istreambuf_iterator<char>(file) ),
                                   (std::istreambuf_iterator<char>()    ) );
    file.close();
    return sourceString;
}

