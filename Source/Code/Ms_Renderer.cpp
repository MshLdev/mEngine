#include "Ms_Renderer.h"

Ms_Renderer::Ms_Renderer()
{
}

void Ms_Renderer::LoadAssets(const char* Path)
{
    Shader_array  = new Ms_Shader[8];
    Mesh_array    = new Ms_Mesh[19];
    Texture_array = new Ms_Textures[14];

    Shader_array[0].Load_Shader("Basic_Phong");
    Shader_array[1].Load_Shader("light");
    Shader_array[2].Load_Shader("ambient");
    Shader_array[3].Load_Shader("Collider");
    Shader_array[4].Load_Shader("sky");
    Shader_array[5].Load_Shader("Ray");
    Shader_array[6].Load_Shader("Toon");
    Shader_array[7].Load_Shader("Deph");

    Mesh_array[0].LoadMesh("Data/mesh/Grid2.obj");
    Mesh_array[1].LoadMesh("Data/mesh/Ms_Box2.obj");
    Mesh_array[2].LoadMesh("Data/mesh/Ms_Box1.obj");
    Mesh_array[3].LoadAnimation("Data/mesh/test_rig.dae");
    Mesh_array[4].LoadAnimation("Data/mesh/CrossBow.dae");
    Mesh_array[4].ImportAnim("Data/Anim/CrossBow.Anim");
    Mesh_array[5].LoadMesh("Data/mesh/mapa1.obj");

    Texture_array[0].LoadTxT("Data/Map/deffuse/Grid2.png");
    Texture_array[1].LoadTxT("Data/Map/deffuse/box.jpg");
    Texture_array[2].LoadTxT("Data/Map/deffuse/Storm.dds");
    Texture_array[6].LoadCubemap("Data/Map/sky/Lake");
    Texture_array[10].LoadTxT("Data/Map/deffuse/CrossBow.png");
    Texture_array[13].LoadTxT("Data/Map/deffuse/scaled.png");

    glGenVertexArrays(1, &SkyVAO);
    glGenBuffers(1, &skyVBO);

   GLfloat skyboxVertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    /// Setup skybox VAO
    glBindVertexArray(SkyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
}


void Ms_Renderer::Draw_Object(int shaderID, int meshID, int textureID, glm::mat4 Position, int animID, float animTime)
{

    GLuint shader = Shader_array[shaderID].ReadyShader;
    GLuint texture = Texture_array[textureID].GetID();

            ///Wybieranie otrzymanego shadera
            glUseProgram(shader);
            ///Przekazywanie uniformow do shaderow...
            ///Kolor który bedzie przeliczany na ambient(vec4)
            GLint objectColorLoc = glGetUniformLocation(shader, "objectColor");
                glUniform3f(objectColorLoc, 0.4f, 0.4f, 0.4f);
            ///Kolor Swiatla
            GLint lightColorLoc  = glGetUniformLocation(shader, "lightColor");
                glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
            ///Pozycja swiatla
            GLint lightPositionLoc  = glGetUniformLocation(shader, "lightPosition");
                glUniform3f(lightPositionLoc, 0.0f, 5.0f, 0.0f);
            ///Rysowany Obiekt(matrix4)
            GLint modelLoc = glGetUniformLocation(shader, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Position));
            ///Kamera(Matrix4)
            GLint modelview = glGetUniformLocation(shader, "view");
                glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(camera.Camera_Matrix));
            ///Projekcja(Matrix4)
            GLint modelproj = glGetUniformLocation(shader, "projection");
                glUniformMatrix4fv(modelproj, 1, GL_FALSE, glm::value_ptr(camera.Projection));
            ///Pozycja Kamery
            GLint viewPosLoc = glGetUniformLocation(shader, "viewPos");
                glUniform3f(viewPosLoc, camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);

        ///Bindowanie textury
        glBindTexture(GL_TEXTURE_2D, texture);

        if(Mesh_array[meshID].isStatic)
            Mesh_array[meshID].Draw_VAO();
        else if(!Mesh_array[meshID].isStatic)
            Mesh_array[meshID].DrawFrame(animID, animTime, Delta);

}
void Ms_Renderer::Update(Ms_Camera cam, float time)
{
        camera = cam;
        Delta = time;

        DrawSky();
}

void Ms_Renderer::DrawSky()
{
    glDepthMask(GL_FALSE);
    glUseProgram(Shader_array[4].ReadyShader);

            ///Kamera wyczyszczona z pozycji
            GLint modelview = glGetUniformLocation(Shader_array[4].ReadyShader, "view");
                glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(camera.Camera_Matrix))));
            ///Projekcja(Matrix4)
            GLint modelproj = glGetUniformLocation(Shader_array[4].ReadyShader, "projection");
                glUniformMatrix4fv(modelproj, 1, GL_FALSE, glm::value_ptr(camera.Projection));

    glBindVertexArray(SkyVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Texture_array[6].GetID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

Ms_Renderer::~Ms_Renderer()
{
    delete [] Shader_array;
    delete [] Mesh_array;
    delete [] Texture_array;
}
