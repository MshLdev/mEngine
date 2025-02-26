#ifndef MS_PREFAB_H
#define MS_PREFAB_H

#include "Ms_CollisionEngine.h"
#include <iostream>
#include <vector>

class Ms_Prefab
{
    public:
        Ms_Prefab();
        virtual ~Ms_Prefab();

        void Setup(int mesh, int texture, int shader, glm::vec3 matrix, bool Dynamic);
        void Transform(glm::vec3 Axis);
        void Update();
        void Set_Bounds(glm::vec3 Pos, float x, float y, float z);
        void Show_Bounds(GLuint shader, glm::mat4 camera, glm::mat4 proj);
        void Refresh_Bounds();

        int Mesh_id;
        int Texture_id;
        int Shader_id;
        int Anim_id;
        float Anim_Timer;


        glm::mat4 Position_Matrix;      ///Pozycja w matrycy dla shadera
        glm::vec3 Velocity;
        Ms_CollisionEngine Collider;
        bool isSOLID;
        bool isDYNAMIC;
        bool isAIRBORN;
        bool isVoxel;
        bool isSPHERE;
};

#endif // MS_PREFAB_H
