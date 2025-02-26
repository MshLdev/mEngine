#ifndef MS_SCENE_H
#define MS_SCENE_H

#include <iostream>

#include "Ms_CollisionEngine.h"
#include "Ms_Prefab.h"
#include "Ms_Player.h"
#include "Ms_Timer.h"
#include "Ms_Renderer.h"
#include <algorithm>

class Ms_Scene
{
    public:
        Ms_Scene();
        virtual ~Ms_Scene();

        void Load_Assets(GLuint width, GLuint height);
        void Update();
        void fPlayer();
        void Mesh_render();
        void Temp_Phsx();
        void ColisionAxis();

            void mouse(double x, double y);
            void Key_UP(int);
            void Key_DOWN(int);

        int NumObj;
        int ticks = 1;
        float passt = 0.0f;
        float DeltaTime;
        bool keys[500];

        Ms_Renderer                 Renderer;
        Ms_Timer                    Timer;
        Ms_Camera                   Camera;
        Ms_Player                   Player;
        Ms_Prefab                   *Prefab_array;
        Ms_Prefab                   Prefab_weapon;
};

#endif // MS_SCENE_H
