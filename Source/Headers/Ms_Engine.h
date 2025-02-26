#include "glad.h"
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Ms_Timer.h"
#include "Ms_Camera.h"
#include "Ms_Shader.h"
#include "Ms_Mesh.h"
#include "Ms_Texture.h"

class Ms_Engine
{
    public:
        Ms_Engine();
        void Init();
        void Load();
        void Draw();
        void Logic();
        void KeyBoard(GLFWwindow* window, int key, int scancode, int action, int mode);
        void Mouse(GLFWwindow* window, double xpos, double ypos);
        virtual ~Ms_Engine();

        GLFWwindow* window;

    protected:
        ///matrixy
        glm::mat4 camera_Matrix, projection_Matrix;
        /// rozdzialka
        GLuint width, height;
        ///tworzenie potrzebnych obiektow
        Ms_Timer ms_timer;
        Ms_Camera Camera;

        int Obj_Index[8][4];                                           //Indexy
        Ms_Shader Shaders[3];                                          //Shadery
        Ms_Mesh Models[8];                                              //Modele
        Ms_Textures Textura[5];                                        //Textury
        glm::mat4 Obj_Matrix[8];                                       //Transformacje

};
