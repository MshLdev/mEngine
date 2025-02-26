#include "glad.h"
#include <GLFW/glfw3.h>
#include "Ms_Scene.h"

    ///rodzialka/obiekty
    const GLuint width = 1200, height = 720;
    Ms_Scene* Scena;


///klawiatura
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        Scena->Key_UP(key);
    if(action == GLFW_RELEASE)
        Scena->Key_DOWN(key);
}
///myszka
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   Scena->mouse(xpos, ypos);
}

int main()
{
    ///inizjalizacja glfw
    glfwInit();
    ///Konfigutacja glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    ///tworzenie okna glfw
    GLFWwindow* window = glfwCreateWindow(width, height, "DarkBoats v(A)0.1 [x86|OGL]", NULL, NULL);
    glfwMakeContextCurrent(window);

    ///Inputy
    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    ///Inicjalizacja silnika
    Ms_Scene scena;
    Scena = &scena;
    Scena->Load_Assets(width, height);

    glfwSwapInterval(0);        ///synchronizacja
    glEnable(GL_DEPTH_TEST);    ///Z-test
    glDepthFunc(GL_LESS);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);///offniecie kursora

    while (!glfwWindowShouldClose(window))
    {
            glfwPollEvents();
            /// Czyszczenie bufora kolorow
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Scena->Update();

            glfwSwapBuffers(window);
    }
    ///Zabijanie glfw... bruudna robota...
    glfwTerminate();
    return 0;
}
