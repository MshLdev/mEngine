#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Ms_Camera
{
    public:
        Ms_Camera();
        void Init(GLuint width, GLuint height);
        void do_movement(float Delta, bool keys[]);
        void mouse_callback(double xpos, double ypos);
        void setMatrix();
        void setProjection();
        glm::vec3 GetPos();
        glm::vec3 GetFront();
        glm::vec3 GetUP();
        virtual ~Ms_Camera();

    GLuint WIDTH; GLuint HEIGHT;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 Camera_2dVector;
    glm::vec3 wep_2dVector;
    glm::vec3 CrossProd;

    glm::mat4 Projection;
    glm::mat4 Camera_Matrix;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat lastX;
    GLfloat lastY;

    bool firstMouse;
    private:
};
#endif
