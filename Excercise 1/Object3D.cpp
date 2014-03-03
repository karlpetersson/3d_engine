//
//  Object3D.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-29.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Object3D.h"

Object3D::Object3D() {
    this->modelMatrix = glm::mat4(1.);
}

void Object3D::translate(glm::vec3 vector) {
    this->modelMatrix = glm::translate(this->modelMatrix, vector);
}

void Object3D::rotate(glm::vec3 vector, float degrees) {
    this->modelMatrix = glm::rotate(this->modelMatrix, degrees, vector);
}

void Object3D::scale(glm::vec3 vector) {
    this->modelMatrix = glm::scale(this->modelMatrix, vector);
}