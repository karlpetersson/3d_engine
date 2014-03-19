//
//  Camera.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-02-03.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__Camera__
#define __Excercise_1__Camera__

#include <iostream>
#include "Object3D.h"
#include <math.h>
#include <glfw3.h>
#include "glm/gtx/rotate_vector.hpp"
#include "constants.h"

class Camera : public Object3D {
public:
    
    bool useBezierMovement;
    
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    
    glm::mat4 view;
    glm::mat4 projection;
    
    float fov;
    float aspectRatio;
    float z_near;
    float z_far;
    
    float horizontalAngle;
    float verticalAngle;
    
    float speed;
    float mouseSpeed;
    float rotSpeed;
    
    float lastTime;
    double prevMouseX;
    double prevMouseY;
    
    glm::vec3 b_start;
    glm::vec3 b_control;
    glm::vec3 b_end;
    
    float velocity;
    float acceleration;
    float accelerationDecay;
    float _t;
    float turnAmount;
    
    glm::vec3 lookatDir;
    glm::vec3 currentPosition;
    glm::vec3 lastPos;
    
    bool turning;
    bool calcNewCurve;
    
    GLFWwindow *window;
    
    Camera(GLFWwindow *window, float fov, float aspectRatio, float z_near, float z_far);
    void updateView();
    void useOrthogonalProjection();
    void usePerspectiveProjection();
    void useObliqueProjection();
    void cursorPosCallback(double x, double y);
    
    glm::vec3 calculateBezierPosition(float t);
    void setBezierCurve(glm::vec3 v_direction);

    void update();
    void updateMovement();
    void updateMovementBezier();
};

#endif /* defined(__Excercise_1__Camera__) */
