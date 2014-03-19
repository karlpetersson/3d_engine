//
//  Camera.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "Camera.h"

Camera::Camera(GLFWwindow *window, float fov, float aspectRatio, float z_near, float z_far) {
    position = glm::vec3(2.0, 1.0, 2.0);
    target = glm::vec3(0.0, 1.0, -1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
    
    useBezierMovement = false;
    
    this->window = window;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->z_near = z_near;
    this->z_far = z_far;
    
    horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    verticalAngle = 0.0f;
    
    speed = 3.0f; // 3 units / second
    rotSpeed = 1.5f;
    mouseSpeed = 0.001f;
    
    lastTime = 0.0f;
    prevMouseX = 0.0;
    prevMouseY = 0.0;
    
    velocity = 0.0;
    acceleration = 0.7;
    accelerationDecay = 0.9;
    turning = false;
    calcNewCurve = false;
    _t = 0.0f;
    turnAmount = 0.0;

    lookatDir = glm::vec3(0.0f, 0.0f, -1.0f);
    lastPos = position;
    b_start = glm::vec3(2.0, 1.0, 2.0);
    b_control = b_start + glm::normalize(lookatDir) * 3.f;
    b_end = b_start + glm::normalize(lookatDir) * 6.f;
    
    //currentPosition = glm::vec3(calculateBezierPosition(_t));

    updateView();
    this->usePerspectiveProjection();
}

void Camera::updateView() {
    this->view = glm::lookAt(position, target, up);
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
    projection = glm::perspective(fov, aspectRatio, z_near, z_far);
}

void Camera::update() {
    if(useBezierMovement) {
        updateMovementBezier();
    } else {
        updateMovement();
    }
}

void Camera::updateMovement() {
    
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    // Mouse movement
   
    //bool movedByMouse = false;
    //if (glfwGetKey(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
    /*double xpos, ypos;
    glfwGetCursorPos(this->window, &xpos, &ypos);
    
    if(abs(xpos - prevMouseX) > 0.1) {
        horizontalAngle -= (xpos - prevMouseX) * 0.001;
        prevMouseX = xpos;
        movedByMouse = true;
    }
    if(abs(ypos - prevMouseY) > 0.1) {
        verticalAngle -= (ypos - prevMouseY) * 0.001;
        prevMouseY = ypos;
        movedByMouse = true;
    }
    
    if(movedByMouse) {
        glfwSetCursorPos(this->window, 800/2, 600/2);
        prevMouseX = 800/2;
        prevMouseY = 600/2;
    }*/
    
   // }
    
    // double xpos, ypos;
    // glfwGetCursorPos(this->window, &xpos, &ypos);
        // Reset mouse position for next frame
    
   // horizontalAngle += mouseSpeed * deltaTime * float(800/2 - xpos );
   // verticalAngle += mouseSpeed * deltaTime * float( 600/2 - ypos );
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        horizontalAngle += rotSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        horizontalAngle -= rotSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        verticalAngle += rotSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        verticalAngle -= rotSpeed * deltaTime;
    }
    
    glm::vec3 m_direction(
                        cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle),
                        cos(verticalAngle) * cos(horizontalAngle)
                        );
    
    glm::vec3 right = glm::vec3(
                                sin(horizontalAngle - 3.14f/2.0f),
                                0,
                                cos(horizontalAngle - 3.14f/2.0f)
                                );
    
    glm::vec3 m_up = glm::cross( right, m_direction );
    glm::vec3 m_position = position;
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_position += m_direction * deltaTime * speed;
    }
    
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_position -= m_direction * deltaTime * speed;
    }
    
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_position -= right * deltaTime * speed;
    }
    
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_position += right * deltaTime * speed;
    }
    
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        m_position -= m_up * deltaTime * speed;
    }
    
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        m_position += m_up * deltaTime * speed;
    }

    position = m_position;
    target = m_position + m_direction;
    up = m_up;
    
    updateView();
    
    lastTime = currentTime;
    
}

void Camera::updateMovementBezier() {
    
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    // foward signal
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity += deltaTime * acceleration;
    // brake signal
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity *= acceleration;
    // if not going forward or back, decay velocity
    } else {
        velocity *= accelerationDecay;
    }
    
    // stop completely if velocity is low
    if(velocity < 0.01f) {
        velocity = 0.0f;
    }
    
    // limit speed to 0.5 maximum, 0 minimum
    velocity = clamp(velocity, 0, 0.5);
    
    // if new turn signal is recieved
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !turning) {
        turning = true;
        turnAmount = 1.f;
        calcNewCurve = true;
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !turning) {
        turning = true;
        turnAmount = -1.f;
        calcNewCurve = true;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        turning = false;
        turnAmount = 0.0f;
    }
    
    _t += deltaTime * velocity;
    glm::vec3 d;
    
    // if still on current curve
    if(_t <= 1.0f) {
        // move along curve
        position = glm::vec3(calculateBezierPosition(_t));
        d = position - lastPos;
        
        // if camera moved a distance larger than 0, update lookat
        if(glm::length(d) > 0.0f) {
            lookatDir = d;
        }
        
        // if turn signal was registered, calculate new bezier curve
        if(turning && calcNewCurve) {
            glm::mat4 rot = glm::rotate(glm::mat4(1.0f), turnAmount*60.f, glm::vec3(0.0f ,1.0f, 0.0f));
            glm::vec3 newRotatedEndPoint = glm::vec3(rot * glm::vec4(glm::normalize(lookatDir), 1.0));
            
            b_start = calculateBezierPosition(_t);
            b_control = b_start + glm::normalize(lookatDir) * 3.f;
            b_end = b_start + newRotatedEndPoint * 6.f;
            
            _t = 0.0f;
            calcNewCurve = false;
        }
    }
    // otherwise calculate new curve
    else {
        b_start = calculateBezierPosition(_t);
        b_control = b_start + glm::normalize(lookatDir) * 3.f;
        b_end = b_start + glm::normalize(lookatDir) * 6.f;
        _t = 0.0f;
    }
    
    lastTime = currentTime;
    lastPos = position;
    
    target = position + lookatDir;

    updateView();
    
}

glm::vec3 Camera::calculateBezierPosition(float t) {
    t = clamp(t, 0.0f, 1.0f);
    return (1 - t) * ((1 - t) * b_start + t * b_control) + t * ((1 - t) * b_control + t * b_end);
}


