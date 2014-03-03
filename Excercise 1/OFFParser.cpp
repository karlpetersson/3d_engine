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

// Parses an OFF from a file
Mesh OFFParser::parse(std::string filename) {
    
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    
    std::string line;
    std::getline(file, line); //skip first line
    std::getline(file, line); //read number of verties/faces/edges from second line
    
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
    
    // for each vertex
    for(int i = 0; i < numVertices; i++) {
        std::getline(file, line);
        ss.clear();
        ss.str(line);
        Vec3 vector;
        Vec3 norm;
        Vertex vertex;
        
        // parse position and normal for current vertex
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
    
    // create a map used to map each vertex do a list of normals that
    // will correspond to that vertex
    std::map <Vertex *, std::vector<glm::vec3>> vertexNormals;
    
    // Repeat for number of faces
    for(int i = 0; i < numFaces; i++) {
        std::getline(file, line);
        std::stringstream ss(line);
        std::vector<int> indices;
        int nVertices;
        ss >> nVertices;
        
        // store indices
        for(int j = 0; j < nVertices; j++) {
            int index;
            ss >> index;
            indices.push_back(index);
        }
        
        size_t len = indices.size();
        
        // perform triangulation
        for(int j = 2; j < len; j++) {
            
            int p1 = indices[0];
            int p2 = indices[j-1];
            int p3 = indices[j];
            
            mesh.indices.push_back(p1);
            mesh.indices.push_back(p2);
            mesh.indices.push_back(p3);
            
            // create a two vectors defining the current face
            glm::vec3 e1 = glm::vec3(mesh.vertices->buffer[p2].pos.x, mesh.vertices->buffer[p2].pos.y, mesh.vertices->buffer[p2].pos.z) - glm::vec3(mesh.vertices->buffer[p1].pos.x, mesh.vertices->buffer[p1].pos.y, mesh.vertices->buffer[p1].pos.z);
            
            glm::vec3 e2 = glm::vec3(mesh.vertices->buffer[p3].pos.x, mesh.vertices->buffer[p3].pos.y, mesh.vertices->buffer[p3].pos.z) - glm::vec3(mesh.vertices->buffer[p1].pos.x, mesh.vertices->buffer[p1].pos.y, mesh.vertices->buffer[p1].pos.z);
            
            // get the normal of the face vector
            glm::vec3 f_norm = glm::cross(e1, e2);
            
            // add the normal to each vertex that defines the current face
            vertexNormals[&mesh.vertices->buffer[p2]].push_back(f_norm);
            vertexNormals[&mesh.vertices->buffer[p3]].push_back(f_norm);
            vertexNormals[&mesh.vertices->buffer[p1]].push_back(f_norm);

        }
    }
    
    // For all vertices
    for (std::map<Vertex *, std::vector<glm::vec3>>::iterator it=vertexNormals.begin(); it!=vertexNormals.end(); ++it) {
        // calculate a mean for all normals(i.e. normals of all faces containing vertex)
        // corresponding to that vertex
        glm::vec3 sumVector = glm::vec3(0.0f);
        for (std::vector<glm::vec3>::iterator itt = it->second.begin() ; itt != it->second.end(); ++itt) {
            sumVector += *itt;
        }
        glm::vec3 normalized = glm::normalize(sumVector);
        it->first->norm.x = normalized.x;
        it->first->norm.y = normalized.y;
        it->first->norm.z = normalized.z;
        
    }
    
    file.close();
    
    return mesh;
}