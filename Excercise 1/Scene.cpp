//
//  Scene.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Scene.h"

Scene::Scene() {
    this->view = glm::mat4(1.);
    this->view = glm::translate(this->view, glm::vec3(0.0f,0.0f, -5.0f));
    this->projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
}

// adds an object to the scene
void Scene::add(Mesh *obj) {
    this->objects.push_back(obj);
}

// adds a light to the scene
void Scene::add(Light *light) {
    this->lights.push_back(light);
}