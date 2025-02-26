#include "Ms_Mesh.h"


Ms_Mesh::Ms_Mesh()
    {
    ///czas na utworzenie wszystkich bufforow
    glGenVertexArrays(1, &VAO_S);   ///
    glGenBuffers(1, &VBO_S);
    glGenBuffers(1, &EBO_S);
    isStatic = true;
    AnimDelay = 0.0f;
    }

void Ms_Mesh::LoadMesh(const char* File)
    {
    ///Wczytywanie modelu do obiektu aiScene z parametrami(wersja funkci jezyka C)
    const aiScene* scene = aiImportFile( File, aiProcess_JoinIdenticalVertices );
    if( !scene)
        std::cout<<"Cos jeblo!![["<<aiGetErrorString()<<File<<"]]\n";


    aiMesh *mesh = scene->mMeshes[0];               ///Wyciaganie meshu z obiektu sceny
    numVerts = mesh->mNumFaces*3;                   ///Pobieranie ilosci Vertexow do rysowania(sciana *3)
    Ms_Vertex New_Vertex_Array[mesh->mNumFaces*3];  ///Tworzenie tabeli vertexow(drugi nowy sposob)


    ///Przechodzimy przez wszystkie vertexy(jest ich mniej niz vertexow do rysowania, dzieki indexowaniu)
    for(unsigned int i=0;i<mesh->mNumVertices;i++)
        {
            ///pobieramy informacje o pozycji, normalach i mapach kazdego vertexu
            aiVector3D pPos = (mesh->mVertices[i]);
            aiVector3D pNormal = (mesh->mNormals[i]);
            aiVector3D pTexCoord =  (mesh->mTextureCoords[0][i]);

            ///przesylamy pobrane dane do tablicy struktury przechowywujacej nasz model
            New_Vertex_Array[i].Pos = glm::vec3(pPos.x, pPos.y, pPos.z);

            if(mesh->HasNormals())
                New_Vertex_Array[i].Norm = glm::vec3(pNormal.x, pNormal.y, pNormal.z);

            if(mesh->HasTextureCoords(0))
                New_Vertex_Array[i].UV = glm::vec2(pTexCoord.x, pTexCoord.y);
        }
        ///Po wczytaniu vertexow jest czas na ich indexy
        Ms_Indeces IndAray[mesh->mNumFaces];

        /// Dostep do indexow uzyskujemy poprzez node aiFace
        for(unsigned int i=0;i<mesh->mNumFaces;i++)
            {
                aiFace Face = mesh->mFaces[i];
                IndAray[i].Vert_1 = Face.mIndices[0];
                IndAray[i].Vert_2 = Face.mIndices[1];
                IndAray[i].Vert_3 = Face.mIndices[2];
            }

        glBindVertexArray(VAO_S);
        ///Buffer Vertexow
        glBindBuffer(GL_ARRAY_BUFFER, VBO_S);
        glBufferData(GL_ARRAY_BUFFER, sizeof(New_Vertex_Array), New_Vertex_Array, GL_STATIC_DRAW);

        ///Buffer Indexow
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_S);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndAray), IndAray, GL_STATIC_DRAW);

            ///Vertexy
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Ms_Vertex), (GLvoid*)0);
            ///uv mapa
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Ms_Vertex), (GLvoid*)(sizeof(glm::vec3)));
            ///Normale
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Ms_Vertex), (GLvoid*)(sizeof(glm::vec3)+sizeof(glm::vec2)));

        ///Odbindowanie buffera vertexow
        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
        std::cout<<"(Liczba Vertexow:"<<mesh->mNumVertices<<")<Liczba Faceow:"<<mesh->mNumFaces<<">"<<"[Liczba rysowanych:"<<mesh->mNumFaces*3<<"]\n==============================================\n";
    }

void Ms_Mesh::ImportAnim(const char* Path)
{
            Animation_File_Header Header;
            Animation_Anim_Struct Struct;
            std::fstream fh;
            fh.open(Path, std::fstream::in | std::fstream::binary);
            fh.read(reinterpret_cast<char *>(&Header), sizeof(Animation_File_Header));
            for(int numAnim = 1; numAnim <= Header.numAnimations; numAnim++)
            {
                Animation.animations.push_back(Animation.animations[0]);
                fh.read(reinterpret_cast<char *>(&Struct), sizeof(Animation_Anim_Struct));
                Animation_File_Data   Data[Struct.numBones];
                Animation.animations[numAnim].ticksPerSecond = Struct.ticks;
                Animation.animations[numAnim].duration = Struct.duration;

                for(int i = 0; i < Struct.numBones; i++)
                {
                fh.read(reinterpret_cast<char *>(&Data[i].boneId), sizeof(unsigned int));
                Animation.animations[numAnim].channels[i].positions.resize(Struct.numFrames);
                Animation.animations[numAnim].channels[i].rotations.resize(Struct.numFrames);
                Animation.animations[numAnim].channels[i].scales.resize(Struct.numFrames);
                    for(int j = 0; j < Struct.numFrames; j++)
                    {
                        aiVectorKey TmpPos;
                        fh.read(reinterpret_cast<char *>(&TmpPos), sizeof(aiVectorKey));
                        Data[i].positions.push_back(TmpPos);
                        Animation.animations[numAnim].channels[i].positions[j] = TmpPos;
                        aiQuatKey TmpRot;
                        fh.read(reinterpret_cast<char *>(&TmpRot), sizeof(aiQuatKey));
                        Data[i].rotations.push_back(TmpRot);
                        Animation.animations[numAnim].channels[i].rotations[j] = TmpRot;
                        aiVectorKey TmpScale;
                        fh.read(reinterpret_cast<char *>(&TmpScale), sizeof(aiVectorKey));
                        Data[i].scales.push_back(TmpScale);
                        Animation.animations[numAnim].channels[i].scales[j] = TmpScale;
                    }
                }
            }
            fh.close();
}

void Ms_Mesh::LoadAnimation(const char* path)
{
    isStatic = false;
    Animation.read(path);
}

void Ms_Mesh::DrawFrame(int num,float time, float delay)
{
    AnimDelay += delay;
    if(AnimDelay >= 0.03f)
    {
        Animation.drawFrame(num, time);
        AnimDelay = 0.0f;
    }
        glBindVertexArray(Animation.Buffers.VAO);
        glDrawArrays(GL_TRIANGLES, 0, Animation.Buffers.numVerts);
        glBindVertexArray(0);
}

void Ms_Mesh::Draw_VAO()
    {
        /*///Wybieranie otrzymanego shadera
        glUseProgram(ReadyShader);

        GLint objectColorLoc = glGetUniformLocation(ReadyShader, "obj");
        GLint lightColorLoc  = glGetUniformLocation(ReadyShader, "lightColor");
        GLint lightPositionLoc  = glGetUniformLocation(ReadyShader, "lightPosition");
        GLint modelLoc = glGetUniformLocation(ReadyShader, "model");
        GLint modelview = glGetUniformLocation(ReadyShader, "view");
        GLint modelproj = glGetUniformLocation(ReadyShader, "projection");

        glUniform3f(objectColorLoc, 0.1f, 0.1f, 0.1f);//kolor obiektu
        glUniform3f(lightColorLoc,  0.8f, 0.8f, 1.0f); //kolor swiatla
        glUniform3f(lightPositionLoc, 0.0f, 5.0f, 0.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));//pozycja
        glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(view));//kamera
        glUniformMatrix4fv(modelproj, 1, GL_FALSE, glm::value_ptr(projection));//projekcja

        ///Bindowanie otrzymanej textury
        glBindTexture(GL_TEXTURE_2D, Texture);*/
        ///Bindowanie tablicy vertexow
        glBindVertexArray(VAO_S);
        glDrawElements(GL_TRIANGLES, numVerts, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

Ms_Mesh::~Ms_Mesh()
    {
        ///destruktory
        glDeleteVertexArrays(1, &VAO_S);
        glDeleteBuffers(1, &VBO_S);
        glDeleteBuffers(1, &EBO_S);
    }

GLuint Ms_Mesh::Get_VAO()
    {
        return VAO_S;
    }

GLuint Ms_Mesh::Get_EBO()
    {
        return EBO_S;
    }
