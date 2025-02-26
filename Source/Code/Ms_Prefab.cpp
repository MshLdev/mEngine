#include "Ms_Prefab.h"

Ms_Prefab::Ms_Prefab()
{
    isSOLID     = false;
    isAIRBORN   = false;
    isVoxel     = false;
    isSPHERE    = false;
    Anim_id     = 0;
    Anim_Timer  = 0.0f;
}

Ms_Prefab::~Ms_Prefab()
{
    //dtor
}

void Ms_Prefab::Setup(int mesh, int texture, int shader, glm::vec3 matrix, bool Dynamic)
{
    isDYNAMIC        = Dynamic;
    Mesh_id          = mesh;
    Texture_id       = texture;
    Shader_id        = shader;
    Position_Matrix  = glm::translate(Position_Matrix, matrix);
}

void Ms_Prefab::Set_Bounds(glm::vec3 Pos, float x, float y, float z)
{
    isSOLID = true;
    isVoxel = true;
    Ms_CollisionEngine tmpCol;
    tmpCol.Create_Bounding(Pos, x, y, z);
    Collider = tmpCol;
}

void Ms_Prefab::Show_Bounds(GLuint shader, glm::mat4 camera, glm::mat4 proj)
{
   if(isSOLID)
        Collider.Draw_Colider(shader, Position_Matrix, camera, proj);
}

void Ms_Prefab::Update()
{
        Collider.Update_Bouding(glm::vec3(Position_Matrix[3]));
}

void Ms_Prefab::Transform(glm::vec3 Axis)
{
    Position_Matrix[3][0] += Axis.x;
    Position_Matrix[3][1] += Axis.y;
    Position_Matrix[3][2] += Axis.z;

    Update();
}

