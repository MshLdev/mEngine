#ifndef MODEL_HPP
#define	MODEL_HPP

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

//Defines how to write a new Material class for Model and SkeletalAnimationModel.
//Especially how to handle textures may change depending on the multimedia library used.
//Used as default class if your model does not contain any specific materials or textures.

class Mesh
{
    public:
        std::vector<aiVector3D> vertices;
        std::vector<aiVector3D> normals;
        std::vector<aiVector2D> textureCoords;

        std::vector<aiFace> faces;
};

template<class MeshType=Mesh>
class Model
{
    public:
        std::vector<MeshType> meshes;

        virtual void read(const char* filename, unsigned int assimpImporterFlags=aiProcessPreset_TargetRealtime_Fast)
        {
            const aiScene* scene = aiImportFile( filename, assimpImporterFlags );
            if(scene)
                read(scene);
        }

    protected:
        virtual void read(const aiScene *scene)
        {
                //Read materials and textures.
                //Read vertices, normals, texture coordinates, and material type
                for(unsigned int cm=0;cm<scene->mNumMeshes;cm++)
                {
                    this->meshes.emplace_back();

                    const aiMesh *mesh = scene->mMeshes[cm];

                    meshes[cm].vertices.resize(mesh->mNumVertices);
                    meshes[cm].normals.resize(mesh->mNumVertices);
                    meshes[cm].textureCoords.resize(mesh->mNumVertices);

                    for(unsigned int cv=0;cv<mesh->mNumVertices;cv++) {
                        meshes[cm].vertices[cv]=mesh->mVertices[cv];
                        meshes[cm].normals[cv]=mesh->mNormals[cv];
                            meshes[cm].textureCoords[cv].x=mesh->mTextureCoords[0][cv].x;
                            meshes[cm].textureCoords[cv].y=mesh->mTextureCoords[0][cv].y;

                    }
                    meshes[cm].faces.resize(mesh->mNumFaces);
                    for(unsigned int cf=0;cf<mesh->mNumFaces;cf++)
                    {
                        meshes[cm].faces[cf]=mesh->mFaces[cf];
                    }
                }
        }
};
#endif	/* MODEL_HPP */
