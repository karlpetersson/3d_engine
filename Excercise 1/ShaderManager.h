//
//  ShaderManager.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-28.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__ShaderManager__
#define __Excercise_1__ShaderManager__

#include <iostream>
#include <fstream>
#include <glew.h>
#include <glfw3.h>
#include <map>
#include "VertexBuffer.h"

class ShaderManager {
private:
    std::map <std::string, GLuint> vertexShaders;
    std::map <std::string, GLuint> fragmentShaders;
    ShaderManager() {};
    ShaderManager(ShaderManager const&);
    void operator=(ShaderManager const&);
    std::string parseSourceFile(std::string filename);
    GLuint loadVertexShader(std::string source);
    GLuint loadFragmentShader(std::string source);
public:
    static ShaderManager& getInstance() {
        static ShaderManager instance;
        return instance;
    }
    GLuint load(std::string vertexShader, std::string fragmentShader);
};

#endif /* defined(__Excercise_1__ShaderManager__) */