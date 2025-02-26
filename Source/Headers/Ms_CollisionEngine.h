#ifndef MS_COLLISIONENGINE_H
#define MS_COLLISIONENGINE_H

#include <algorithm>
#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ms_CollisionEngine
{
    public:
        Ms_CollisionEngine();
        virtual ~Ms_CollisionEngine();
        void Create_Bounding(glm::vec3 Pos, float x, float y, float z);
        void Update_Bouding(glm::vec3 off);
        bool Check_Bounding(Ms_CollisionEngine Obj);
        bool Check_RayHit(glm::vec3 start, glm::vec3 End);
        void HitResp();
        void Draw_Colider(GLuint Shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj);

        bool Hit;
        glm::vec3 Position;///nic wiecej jak offset colidera
        glm::vec3 Verts[8];
        float Size_X, Size_y, Size_Z;

        glm::vec3 AxisMin;
        glm::vec3 AxisMax;

    protected:
         GLuint VBO_S, VAO_S, EBO_S;

};

#endif // MS_COLLISIONENGINE_H
