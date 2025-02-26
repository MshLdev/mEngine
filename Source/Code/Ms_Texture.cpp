#include "Ms_Texture.h"

Ms_Textures::Ms_Textures()
{
    ilInit();
}

void Ms_Textures::LoadTxT(char const * const File)
{
    ILuint imageID;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);

    ilLoadImage(File);

    ILubyte * data = ilGetData();
    if(!data)
    {
        ilBindImage(0);
        ilDeleteImages(1, &imageID);
    }

    int const width  = ilGetInteger(IL_IMAGE_WIDTH);
    int const height = ilGetInteger(IL_IMAGE_HEIGHT);
    int const type   = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
    int const format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, Ms_Textures::textureID);

    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // rows are tightly packed
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // pixels are tightly packed

        ///Tutaj zachodzi ten tajemniczy proces :O
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);

    ///Interpolacja
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Ms_Textures::LoadCubemap(std::string Source)
{
    std::vector<std::string> faces = String_Join(Source);
    ILuint imageID;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Ms_Textures::textureID);

     for(GLuint i = 0; i < faces.size(); i++)
     {
        const char * c = faces[i].c_str();
        ilLoadImage(c);

        ILubyte * data = ilGetData();

        int const width  = ilGetInteger(IL_IMAGE_WIDTH);
        int const height = ilGetInteger(IL_IMAGE_HEIGHT);
        int const type   = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
        int const format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL


        glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // rows are tightly packed
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // pixels are tightly packed

            ///Tutaj zachodzi ten tajemniczy proces :O
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, type, data);
     }

    ///Interpolacja
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

std::vector<std::string> Ms_Textures::String_Join(std::string File)
{
    std::vector<std::string> faces;
            faces.push_back(File+std::string("_right.jpg"));
            faces.push_back(File+std::string("_left.jpg"));
            faces.push_back(File+std::string("_top.jpg"));
            faces.push_back(File+std::string("_bottom.jpg"));
            faces.push_back(File+std::string("_back.jpg"));
            faces.push_back(File+std::string("_front.jpg"));
    return faces;
}

GLuint Ms_Textures::GetID()
{
    return  Ms_Textures::textureID;
}

Ms_Textures::~Ms_Textures()
{
}
