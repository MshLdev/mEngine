/// GLFW
#include <GLFW/glfw3.h>
///
#include <vector>
#include <string>
#include <iostream>
///devil
#include <GL/glext.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


class Ms_Textures
{
    public:
        Ms_Textures();
        virtual ~Ms_Textures();

        void LoadTxT(char const * const File);
        void LoadCubemap(std::string Source);
        std::vector<std::string> String_Join(std::string File);
        GLuint GetID();

    protected:
        GLuint textureID;
};
