//
//  ShaderManager.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "ShaderManager.h"

// loads and compiles two shaders(one vertexshader and one fragmentshader) and
// creates a shader program
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
    if(!shaderStatusOK(vertexShader)) {
        throw "vertex shader failed to compile";
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
    if(!shaderStatusOK(fragmentShader)) {
        throw "Fragment shader failed to compile";
    }
    
    fragmentShaders[source] = fragmentShader;
    return fragmentShader;
    
}

// Parses a shader source file
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

// Checks if a shader compiled correctly
bool ShaderManager::shaderStatusOK(int shaderId) {
    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shaderId, 512, NULL, buffer);
        
        std::string err(buffer);
        std::cerr << err << std::endl;
        
        return false;
    }
    
    return true;
}

