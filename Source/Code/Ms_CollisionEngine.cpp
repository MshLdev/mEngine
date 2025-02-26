#include "Ms_CollisionEngine.h"

Ms_CollisionEngine::Ms_CollisionEngine()
{
 ///czas na utworzenie wszystkich bufforow
    glGenVertexArrays(1, &VAO_S);
    glGenBuffers(1, &VBO_S);
    glGenBuffers(1, &EBO_S);
    Hit = false;
}

Ms_CollisionEngine::~Ms_CollisionEngine()
{
    //dtor
}

void Ms_CollisionEngine::Create_Bounding(glm::vec3 Pos, float x, float y, float z)
{


    Ms_CollisionEngine::Position = Pos;
    Ms_CollisionEngine::Size_X = x/2;
    Ms_CollisionEngine::Size_y = y;
    Ms_CollisionEngine::Size_Z = z/2;

    Verts[0] = glm::vec3(Position.x + Size_X, Position.y + Size_y, Position.z + Size_Z);
    Verts[1] = glm::vec3(Position.x + Size_X, Position.y + Size_y, Position.z - Size_Z);
    Verts[2] = glm::vec3(Position.x - Size_X, Position.y + Size_y, Position.z + Size_Z);
    Verts[3] = glm::vec3(Position.x - Size_X, Position.y + Size_y, Position.z - Size_Z);

    Verts[4] = glm::vec3(Position.x + Size_X, Position.y, Position.z + Size_Z);
    Verts[5] = glm::vec3(Position.x + Size_X, Position.y, Position.z - Size_Z);
    Verts[6] = glm::vec3(Position.x - Size_X, Position.y, Position.z + Size_Z);
    Verts[7] = glm::vec3(Position.x - Size_X, Position.y, Position.z - Size_Z);

    Update_Bouding(Pos);
    GLuint indices[] = {
        0, 1,
        1, 3,
        3, 2,
        2, 0,

        4, 5,
        5, 7,
        7, 6,
        6, 4,

        1, 5,
        3, 7,
        2, 6,
        0, 4,
    };

    glBindVertexArray(VAO_S);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_S);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_S);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void Ms_CollisionEngine::Draw_Colider(GLuint Shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj)
{
        glLineWidth(3.0f);
         glUseProgram(Shader);

        ///Stan kolidera
        GLint ColState  = glGetUniformLocation(Shader, "State");
        if(Hit)
            glUniform3f(ColState,  1.0f, 0.0f, 0.0f);
        else
            glUniform3f(ColState,  0.0f, 1.0f, 0.0f);
        ///Rysowany Obiekt(matrix4)
        GLint modelLoc = glGetUniformLocation(Shader, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ///Kamera(Matrix4)
        GLint modelview = glGetUniformLocation(Shader, "view");
            glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(view));
        ///Projekcja(Matrix4)
        GLint modelproj = glGetUniformLocation(Shader, "projection");
            glUniformMatrix4fv(modelproj, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(VAO_S);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}
///owad
void Ms_CollisionEngine::Update_Bouding(glm::vec3 off)
{
    off += Position;
    AxisMin = glm::vec3(off.x - Size_X, off.y, off.z - Size_Z);
    AxisMax = glm::vec3(off.x + Size_X, off.y + Size_y, off.z + Size_Z);
}

bool Ms_CollisionEngine::Check_Bounding(Ms_CollisionEngine Obj)
{
  return (AxisMin.x <= Obj.AxisMax.x && AxisMax.x >= Obj.AxisMin.x) &&
         (AxisMin.y <= Obj.AxisMax.y && AxisMax.y >= Obj.AxisMin.y) &&
         (AxisMin.z <= Obj.AxisMax.z && AxisMax.z >= Obj.AxisMin.z);
}

bool Ms_CollisionEngine::Check_RayHit(glm::vec3 org, glm::vec3 dir)
{
    glm::vec3 dirfrac;
    /// r.dir is unit direction vector of ray
    dirfrac.x = 1.0f / dir.x;
    dirfrac.y = 1.0f / dir.y;
    dirfrac.z = 1.0f / dir.z;
    /// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    /// r.org is origin of ray
    float t1 = (AxisMin.x - org.x)*dirfrac.x;
    float t2 = (AxisMax.x - org.x)*dirfrac.x;
    float t3 = (AxisMin.y - org.y)*dirfrac.y;
    float t4 = (AxisMax.y - org.y)*dirfrac.y;
    float t5 = (AxisMin.z - org.z)*dirfrac.z;
    float t6 = (AxisMax.z - org.z)*dirfrac.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    /// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    float t;
    if (tmax < 0)
    {
        t = tmax;
        return false;
    }

    /// if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        t = tmax;
        return false;
    }

    t = tmin;
    return true;
}

void Ms_CollisionEngine::HitResp()
{
        Hit = !Hit;
}
