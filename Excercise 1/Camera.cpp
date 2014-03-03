//
//  Camera.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Camera.h"

Camera::Camera() {
    position = glm::vec3(2.0, 0.5, 2.0);
    target = glm::vec3(0.0, 1.0, 0.0);
    up = glm::vec3(0.0, 1.0, 0.0);
    
    updateView();
    
    //this->view = glm::translate(this->view, glm::vec3(0.0f,0.0f, -5.0f));
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    
}

void Camera::useOrthogonalProjection() {
    projection = glm::ortho(-5.0f,5.0f,-5.0f,5.0f,-100.0f,100.0f);
}

void Camera::useObliqueProjection() {
    glm::mat4 orthogonalProjection = glm::ortho(-5.0f,5.0f,-5.0f,5.0f,-100.0f,100.0f);
    projection = orthogonalProjection * glm::transpose(
                            glm::mat4(1,0,-0.5 * glm::cos(26.565f/180.0f * M_PI),0,
                                      0,1,-0.5 * glm::sin(26.565f/180.0f * M_PI),0,
                                      0,0,1,0,
                                      0,0,0,1));

}

void Camera::usePerspectiveProjection() {
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
}

void Camera::updateView() {
    this->view = glm::lookAt(position, target, up);
}