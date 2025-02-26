#include "Ms_Timer.h"

Ms_Timer::Ms_Timer()
{
    ///Zerowanie zmiennych (konstruktor)
    Ms_Timer::deltaTime = 0.0f;
    Ms_Timer::lastFrame = 0.0f;
    Ms_Timer::Elapsed = 0.0f;
}

GLfloat Ms_Timer::GetDeltaTime()
{
    ///Zwraca Delte
    return Ms_Timer::deltaTime;
}

GLfloat Ms_Timer::GetElapsed()
{
    ///Zwraca Delte
    return Ms_Timer::Elapsed;
}

void Ms_Timer::TimerUpdate()
{
    ///obliczamy nowy delta-time
    GLfloat currentFrame = glfwGetTime();
    Elapsed = currentFrame;
    Ms_Timer::deltaTime = currentFrame - lastFrame;
    Ms_Timer::lastFrame = currentFrame;
}

Ms_Timer::~Ms_Timer()
{
    ///dtor
}
