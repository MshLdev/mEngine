#ifndef MS_RENDERER_H
#define MS_RENDERER_H

#include "Ms_Mesh.h"
#include "Ms_Texture.h"
#include "Ms_Shader.h"
#include "Ms_Camera.h"

class Ms_Renderer
{
    public:
        Ms_Renderer();
        void LoadAssets(const char* Path);
        void Draw_Object(int Shader, int Mesh, int Texture, glm::mat4 Position, int animID, float animTime);
        void Update(Ms_Camera cam, float time);
        void DrawSky();
        virtual ~Ms_Renderer();

        Ms_Shader                   *Shader_array;            ///Shadery

    protected:
        Ms_Camera camera;
        float Delta;


        Ms_Mesh                     *Mesh_array;              ///Modele
        Ms_Textures                 *Texture_array;           ///Textury

        GLuint                      SkyVAO, skyVBO;
};

#endif // MS_RENDERER_H
