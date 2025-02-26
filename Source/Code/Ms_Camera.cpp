#include "Ms_Camera.h"

Ms_Camera::Ms_Camera()
{
}

void Ms_Camera::Init(GLuint width, GLuint height)
{
    firstMouse = true;
    Ms_Camera::WIDTH = width; Ms_Camera::HEIGHT = height;
    Ms_Camera::cameraPos   = glm::vec3(20.0f, 12.0f, 13.0f);
    Ms_Camera::cameraFront = glm::vec3(-0.4f, -0.6f, -0.7f);
    Ms_Camera::cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    Ms_Camera::yaw   =   180.0f;
    Ms_Camera::pitch =   -30.0f;
    Ms_Camera::setProjection();
}

void Ms_Camera::do_movement(float Delta, bool keys[])
{
    GLfloat cameraSpeed = 5.0f * Delta;
    if(keys[GLFW_KEY_W])
        Ms_Camera::cameraPos += cameraSpeed * cameraFront;
    if(keys[GLFW_KEY_S])
        Ms_Camera::cameraPos -= cameraSpeed * cameraFront;
    if(keys[GLFW_KEY_A])
        Ms_Camera::cameraPos -= glm::normalize(glm::cross(Ms_Camera::cameraFront, Ms_Camera::cameraUp)) * cameraSpeed;
    if(keys[GLFW_KEY_D])
        Ms_Camera::cameraPos += glm::normalize(glm::cross(Ms_Camera::cameraFront, Ms_Camera::cameraUp)) * cameraSpeed;
}

void Ms_Camera::mouse_callback(double xpos, double ypos)
{
    if(Ms_Camera::firstMouse)
    {
        Ms_Camera::lastX = xpos;
        Ms_Camera::lastY = ypos;
        Ms_Camera::firstMouse = false;
    }

    GLfloat xoffset = xpos - Ms_Camera::lastX;
    GLfloat yoffset = Ms_Camera::lastY - ypos;
    Ms_Camera::lastX = xpos;
    Ms_Camera::lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Ms_Camera::yaw   += xoffset;
    Ms_Camera::pitch += yoffset;

    if(Ms_Camera::pitch > 89.0f)
        Ms_Camera::pitch = 89.0f;
    if(Ms_Camera::pitch < -89.0f)
        Ms_Camera::pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Ms_Camera::cameraFront = glm::normalize(front);

    Camera_2dVector = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
    CrossProd = glm::normalize(glm::cross(Ms_Camera::cameraFront, Ms_Camera::cameraUp));
}

void Ms_Camera::setMatrix()
{
    Camera_Matrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
void Ms_Camera::setProjection()
{
    Projection = glm::perspective(glm::radians(75.0f), (GLfloat)WIDTH/ (GLfloat)HEIGHT, 0.05f, 6000.0f);
}

glm::vec3 Ms_Camera::GetPos()
{
    return Ms_Camera::cameraPos;
}

glm::vec3 Ms_Camera::GetFront()
{
    return Ms_Camera::cameraFront;
}

glm::vec3 Ms_Camera::GetUP()
{
    return Ms_Camera::cameraUp;
}

Ms_Camera::~Ms_Camera()
{
    //dtor
}
