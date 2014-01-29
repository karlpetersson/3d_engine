//
//  OFFParser.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include <fstream>
#include <string>
#include <sstream>
#include "OFFParser.h"

Mesh OFFParser::parse(std::ifstream *file) {
        
    std::string line;
    std::getline(*file, line); //skip first line
    std::getline(*file, line);
    
    int numVertices = 0;
    int numFaces = 0;
    int numEdges = 0;
    
    std::stringstream ss(line);
    
    ss >> numVertices;
    ss >> numFaces;
    ss >> numEdges;
    
    std::cout << numVertices << std::endl;
    std::cout << numFaces << std::endl;
    std::cout << numEdges << std::endl;

    
    Mesh mesh = Mesh(numVertices);
    
    for(int i = 0; i < numVertices; i++) {
        std::getline(*file, line);
        ss.clear();
        ss.str(line);
        Vec3 vector;
        Vec3 norm;
        Vertex vertex;

        ss >> vector.x;
        ss >> vector.y;
        ss >> vector.z;
        
        norm.x = 0;
        norm.y = 0;
        norm.z = 0;

        vertex.pos = vector;
        vertex.norm = norm;
                
        mesh.vertices->buffer[i] = vertex;
    }
    
    for(int i = 0; i < numFaces; i++) {
        std::getline(*file, line);
        std::stringstream ss(line);
        std::vector<int> indices;
        int nVertices;
        ss >> nVertices;
        for(int j = 0; j < nVertices; j++) {
            int index;
            ss >> index;
            indices.push_back(index);
        }
                
        size_t len = indices.size();
        for(int j = 2; j < len; j++) {
            mesh.indices.push_back(indices[0]);
            mesh.indices.push_back(indices[j-1]);
            mesh.indices.push_back(indices[j]);
        }
        
    }
    
    return mesh;
}