#include "Ms_Engine.h"

///*///////////////////////////////////////////////////////////////
///*/////////////////////////////////////////////////////////////////
                                                                   ///
Ms_Engine* Ptr = nullptr;                                          ///
void Keyboard_handler(GLFWwindow* a, int b, int c, int d, int e)   ///
{                                                                  ///Handler dla
    if (Ptr)                                                       ///Funkcji C liba Glfw
        Ptr->KeyBoard(a, b, c, d, e);                              ///
}                                                                  ///
                                                                   ///
void Mouse_handler(GLFWwindow* a, double b, double c)              ///
{                                                                  ///
    if (Ptr)                                                       ///
        Ptr->Mouse(a, b, c);                                       ///
}                                                                  ///
                                                                   ///
///*/////////////////////////////////////////////////////////////////
///*///////////////////////////////////////////////////////////////

Ms_Engine::Ms_Engine()
{
    Ms_Engine::width = 1280;
    Ms_Engine::height = 720;
}

void Ms_Engine::Init()
{
    Ms_Engine::Camera.Init(Ms_Engine::width, Ms_Engine::height);
    Ptr = this;

    glfwInit();
    /// Ustawianie opcji glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /// tworzenie okna
    GLFWwindow* window = glfwCreateWindow(width, height, "DarkBoats v(A)0.1 [x86|OGL]", NULL, NULL);
    glfwMakeContextCurrent(window);

    ///Projekcja
    projection_Matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    ///Funkcje inputow
    glfwSetKeyCallback(window, Keyboard_handler);
    glfwSetCursorPosCallback(window, Mouse_handler);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    ///synchronizacja
    glfwSwapInterval(0);
    ///z-buffor
    glEnable(GL_DEPTH_TEST);
    ///kursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Ms_Engine::Load()
{
    Shaders[0].Load_Shader("test");
    Shaders[1].Load_Shader("light");
    Shaders[2].Load_Shader("ambient");

    Models[0].LoadMesh("Data/World/Shape/Grid.obj");
    Models[1].LoadMesh("Data/World/Shape/Ms_Box2.obj");
    Models[2].LoadMesh("Data/World/Shape/Storm.obj");
    Models[3].LoadMesh("Data/World/Shape/storm.dae");
    Models[4].LoadMesh("Data/World/Shape/Skeletal_test3.dae");//dla kosci funkcja loadAnim
    Models[5].LoadMesh("Data/World/Shape/Skeletal_test.dae");
    Models[6].LoadMesh("Data/World/Shape/boat.obj");
    Models[7].LoadMesh("Data/World/Shape/bulb.obj");

    Textura[0].LoadTxT("Data/World/View/Grid.png");
    Textura[1].LoadTxT("Data/World/View/box.jpg");
    Textura[2].LoadTxT("Data/World/View/Storm.dds");
    Textura[3].LoadTxT("Data/World/View/box.jpg");
    Textura[4].LoadTxT("Data/World/View/boat_d.png");


    Obj_Matrix[0] = glm::translate(Obj_Matrix[0], glm::vec3(0.0f, 0.0f, 0.0f));
    Obj_Matrix[1] = glm::translate(Obj_Matrix[1], glm::vec3(8.0f, 0.0f, -8.0f));
    Obj_Matrix[2] = glm::translate(Obj_Matrix[2], glm::vec3(6.0f, 0.0f, 1.0f));
    Obj_Matrix[3] = glm::translate(Obj_Matrix[3], glm::vec3(2.0f, 0.0f, 2.0f));
    Obj_Matrix[4] = glm::translate(Obj_Matrix[4], glm::vec3(-5.0f, 0.0f, -3.0f));
    Obj_Matrix[5] = glm::translate(Obj_Matrix[5], glm::vec3(-6.0f, 0.0f, 4.0f));
    Obj_Matrix[6] = glm::translate(Obj_Matrix[6], glm::vec3(-1.0f, 0.0f, -5.0f));
    Obj_Matrix[7] = glm::translate(Obj_Matrix[7], glm::vec3(0.0f, 5.0f, 0.0f));

    Obj_Index[0][0] = 2; Obj_Index[0][1] = 0; Obj_Index[0][2] = 0; Obj_Index[0][3] = 0;
    Obj_Index[1][0] = 0; Obj_Index[1][1] = 1; Obj_Index[1][2] = 1; Obj_Index[1][3] = 1;
    Obj_Index[2][0] = 0; Obj_Index[2][1] = 2; Obj_Index[2][2] = 2; Obj_Index[2][3] = 2;
    Obj_Index[3][0] = 0; Obj_Index[3][1] = 3; Obj_Index[3][2] = 2; Obj_Index[3][3] = 3;
    Obj_Index[4][0] = 0; Obj_Index[4][1] = 4; Obj_Index[4][2] = 1; Obj_Index[4][3] = 4;
    Obj_Index[5][0] = 0; Obj_Index[5][1] = 5; Obj_Index[5][2] = 1; Obj_Index[5][3] = 5;
    Obj_Index[6][0] = 0; Obj_Index[6][1] = 6; Obj_Index[6][2] = 4; Obj_Index[6][3] = 6;
    Obj_Index[7][0] = 1; Obj_Index[7][1] = 7; Obj_Index[7][2] = 1; Obj_Index[7][3] = 7;
}

void Ms_Engine::Draw()
{
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < 8 ; i++)
            Models[i].Render_Mesh(Shaders[Obj_Index[i][0]].ReadyShader, Textura[Obj_Index[i][2]].GetID(), Obj_Matrix[Obj_Index[i][3]], camera_Matrix, projection_Matrix);

    glfwSwapBuffers(window);
}

void Ms_Engine::Logic()
{
    Ms_Engine::ms_timer.TimerUpdate();
    Ms_Engine::Camera.do_movement(ms_timer.GetDeltaTime());
    Ms_Engine::camera_Matrix = glm::lookAt(Ms_Engine::Camera.GetPos(), Ms_Engine::Camera.GetPos() + Ms_Engine::Camera.GetFront(), Ms_Engine::Camera.GetUP());
}

void Ms_Engine::KeyBoard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        Ms_Engine::Camera.Key_UP(key);
    if(action == GLFW_RELEASE)
        Ms_Engine::Camera.Key_DOWN(key);
}

void Ms_Engine::Mouse(GLFWwindow* window, double xpos, double ypos)
{
    Camera.mouse_callback(xpos, ypos);
}

Ms_Engine::~Ms_Engine()
{
    glfwTerminate();
}
