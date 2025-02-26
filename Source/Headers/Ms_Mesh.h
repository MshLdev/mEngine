#include "glad.h"
#include <iostream>
#include <fstream>
#include <ASSIMP/cimport.h>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>
///GLFW
#include <GLFW/glfw3.h>
///Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
///Skeletal
#include "skeletal_animation_model.hpp"

struct Animation_File_Header
    {
        int Vr;
        int numAnimations;
    };

struct Animation_Anim_Struct
    {
       int numBones;
       int numFrames;
       double duration;
       double ticks;
    };

struct Animation_File_Data
    {
        unsigned int boneId;
        std::vector<aiVectorKey> positions;
        std::vector<aiQuatKey> rotations;
        std::vector<aiVectorKey> scales;
    };

struct Ms_Vertex
    {
        glm::vec3   Pos;
        glm::vec2   UV;
        glm::vec3   Norm;
    };

struct Ms_Indeces
    {
       GLuint   Vert_1;
       GLuint   Vert_2;
       GLuint   Vert_3;
    };

class Ms_Mesh
{
    public:
                    Ms_Mesh();                      ///inizjalizacja bufferow
        void        LoadMesh(const char*);          ///Laduje dane przez assimp
        void        LoadAnimation(const char*);
        void        DrawFrame(int num,float time, float delay);
        void        ImportAnim(const char*);
        virtual     ~Ms_Mesh();                     ///niszczenie
        GLuint      Get_VAO();                      ///cale info o vertexach
        GLuint      Get_EBO();                      ///cale info o indexach{??}
        void        Draw_VAO();                     ///rysowanie

    bool isStatic;
    SkeletalAnimationModel<>    Animation;
    int                         numVerts;        ///liczba vertexow do rysowania (wiecej niz vertexow zadeklarowanych)
    int                         VertSize;        /// rozmiar dynamicznej ablicy w bajtach
    int                         IndSize;         /// rozmiar dynamicznej tablicy w bajtach
    float                       AnimDelay;

    protected:
    GLuint VBO_S, VAO_S, EBO_S;


};

