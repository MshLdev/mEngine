#include "Ms_Scene.h"


Ms_Scene::Ms_Scene()
{
    for(int i = 0; i<= 254; i++)
        keys[i] = false;

    ///Zawsze Pierwszy, gracz jest standardowy dynamicznym prefabem.
    Player.Body_id = 6;
    Player.Wep_id = 4;
    ///Standardowy statyczny  prefab dla prostoty ostatni
}

Ms_Scene::~Ms_Scene()
{
    ///PREFAB to dynamiczna tablica
    delete [] Prefab_array;
}
///DO LOADERA
void Ms_Scene::Load_Assets(GLuint width, GLuint height)
{
    Camera.Init(width, height);
    Camera.mouse_callback(0.1f, 0.1f);
    Renderer.LoadAssets("TEST PATH");

    Prefab_weapon.Setup(4, 10, 0, glm::vec3(0.0f, 0.0f, 0.0f), false);///BRON GRACZA

    NumObj = 7;
    Prefab_array = new Ms_Prefab[NumObj];

    Prefab_array[0].Setup(0, 0, 0, glm::vec3(0.0f, 0.0f, 0.0f), false);///GRID
    Prefab_array[1].Setup(5, 13, 0, glm::vec3(0.0f, 0.1f, 0.0f), true);///MAPA
    Prefab_array[2].Setup(3, 2, 6, glm::vec3(10.0f, 0.0f, 9.0f), true);///Stormer
    Prefab_array[3].Setup(1, 1, 0, glm::vec3(4.0f, 10.0f, 5.0f), true);///Karton1
    Prefab_array[4].Setup(2, 1, 0, glm::vec3(4.0f, 15.0f, 6.0f), true);///Karton2
    Prefab_array[5].Setup(1, 1, 0, glm::vec3(5.0f, 19.0f, 5.0f), true);///Karton3
    Prefab_array[6].Setup(2, 0, 0, glm::vec3(10.0f, 4.0f, 9.0f), true);///player

    Prefab_array[0].Set_Bounds(glm::vec3(0.0f, -1.0f, 0.0f), 30.0f, 1.0f, 30.0f);///Grid
    Prefab_array[3].Set_Bounds(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 2.88f, 2.0f);///Karton1
    Prefab_array[4].Set_Bounds(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f);///Karton2
    Prefab_array[5].Set_Bounds(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 2.88f, 2.0f);///Karton3
    Prefab_array[6].Set_Bounds(glm::vec3(0.0f, 0.0f, 0.0f), 1.3f, 2.0f, 1.3f);///player
}

void Ms_Scene::Update()
{
    Timer.TimerUpdate();
    DeltaTime = Timer.GetDeltaTime();

    ///Gracz
    fPlayer();

    Renderer.Update(Camera,DeltaTime);
    Temp_Phsx();
    Mesh_render();
}

void Ms_Scene::fPlayer()
{
    Camera.cameraPos = Player.Get_Pos(Prefab_array[Player.Body_id]);
    Camera.setMatrix();

    Player.Anim_Timer += DeltaTime;
    Prefab_array[Player.Body_id].Velocity = Player.Movement(Camera, keys);
    Prefab_weapon.Mesh_id = Player.Wep_id;
    Prefab_weapon.Position_Matrix = Player.Set_FPS_Matrix(Camera);
    Prefab_weapon.Anim_id = Player.Anim_id;
    Prefab_weapon.Anim_Timer = Player.Anim_Timer;

    Player.Jump(keys, DeltaTime);
    Player.UseWeapon(keys, DeltaTime);
}

void Ms_Scene::Mesh_render()
{
    for(int i = 0; i <= NumObj-1 ; i++)
    {
        Prefab_array[i].Anim_Timer += Timer.GetDeltaTime();
        Prefab_array[i].Update();
        Prefab_array[i].Show_Bounds(Renderer.Shader_array[3].ReadyShader, Camera.Camera_Matrix, Camera.Projection);
        Prefab_array[i].Velocity.y = -0.1f;

        if(i != Player.Body_id)
        Renderer.Draw_Object(Prefab_array[i].Shader_id
                                ,Prefab_array[i].Mesh_id
                                ,Prefab_array[i].Texture_id
                                ,Prefab_array[i].Position_Matrix
                                ,Prefab_array[i].Anim_id
                                ,Prefab_array[i].Anim_Timer);
    }
     glClear(GL_DEPTH_BUFFER_BIT);
     Renderer.Draw_Object(Prefab_weapon.Shader_id
                                ,Prefab_weapon.Mesh_id
                                ,Prefab_weapon.Texture_id
                                ,Prefab_weapon.Position_Matrix
                                ,Prefab_weapon.Anim_id
                                ,Prefab_weapon.Anim_Timer);
}

///ZA WIELKIE, WYJEBAC
void Ms_Scene::Temp_Phsx()
{
    glm::vec3 AimVec = Camera.cameraPos+Camera.cameraFront - Camera.cameraPos;
    AimVec *= 50;

    for(int i = 0; i <= NumObj-1 ; i++)
        if(Prefab_array[i].isDYNAMIC && Prefab_array[i].isVoxel)
            if(Player.isShooting)
                if(Prefab_array[i].Collider.Check_RayHit(Camera.GetPos(), AimVec) && i != Player.Body_id)
                    Prefab_array[i].Collider.HitResp();

    ///0.008 --> daje nam 124 ticki na sekunde :O
    passt += DeltaTime;
    if(passt < 0.008)
    {}
    else if(passt >= 0.008)
    {
        ticks = int(passt/0.008);

        for(int k = 0; k < ticks; k++)
        for(int i = 0; i <= NumObj-1 ; i++)
        {
                if(Prefab_array[i].isDYNAMIC && Prefab_array[i].isVoxel)
                {

                        ///Kolizja Y:
                        Prefab_array[i].Transform(glm::vec3(0.0f, Prefab_array[i].Velocity.y, 0.0f));
                        if(Prefab_array[i].Velocity.y != 0.0)
                        for(int j = 0; j <= NumObj-1 ; j++)
                            if(i!=j && Prefab_array[j].isSOLID && Prefab_array[j].isVoxel && Prefab_array[i].Collider.Check_Bounding(Prefab_array[j].Collider))
                                {
                                    if((Prefab_array[i].Collider.AxisMax.y - Prefab_array[j].Collider.AxisMin.y) < (Prefab_array[j].Collider.AxisMax.y - Prefab_array[i].Collider.AxisMin.y)  )
                                        Prefab_array[i].Position_Matrix[3][1] = Prefab_array[j].Collider.AxisMin.y - 0.001 - Prefab_array[i].Collider.Size_y;
                                    else
                                        Prefab_array[i].Position_Matrix[3][1] = Prefab_array[j].Collider.AxisMax.y + 0.001;
                                    Prefab_array[i].Velocity.y = 0.0f;
                                    break;
                                }

                        ///Kolizja X:
                        Prefab_array[i].Transform(glm::vec3(Prefab_array[i].Velocity.x, 0.0f, 0.0f));
                        if(Prefab_array[i].Velocity.x != 0.0)
                        for(int j = 0; j <= NumObj-1 ; j++)
                            if(i!=j && Prefab_array[j].isSOLID && Prefab_array[i].Collider.Check_Bounding(Prefab_array[j].Collider))
                                {
                                    if(Prefab_array[i].Collider.AxisMax.y - Prefab_array[j].Collider.AxisMax.y >= 1.5f)
                                        Prefab_array[i].Position_Matrix[3][1] = Prefab_array[j].Collider.AxisMax.y + 0.001;
                                    else if((Prefab_array[i].Collider.AxisMax.x - Prefab_array[j].Collider.AxisMin.x) < (Prefab_array[j].Collider.AxisMax.x - Prefab_array[i].Collider.AxisMin.x))
                                        Prefab_array[i].Position_Matrix[3][0] = Prefab_array[j].Collider.AxisMin.x- 0.001 - Prefab_array[i].Collider.Size_X;
                                    else
                                        Prefab_array[i].Position_Matrix[3][0] = Prefab_array[j].Collider.AxisMax.x+ 0.001 + Prefab_array[i].Collider.Size_X;
                                    Prefab_array[i].Velocity.x = 0.0f;
                                    break;
                                }

                        ///Kolizja Z:
                        Prefab_array[i].Transform(glm::vec3(0.0f, 0.0f, Prefab_array[i].Velocity.z));
                        if(Prefab_array[i].Velocity.z != 0.0)
                        for(int j = 0; j <= NumObj-1 ; j++)
                            if(i!=j && Prefab_array[j].isSOLID && Prefab_array[i].Collider.Check_Bounding(Prefab_array[j].Collider))
                                {
                                    if(Prefab_array[i].Collider.AxisMax.y - Prefab_array[j].Collider.AxisMax.y >= 1.5f)
                                        Prefab_array[i].Position_Matrix[3][1] = Prefab_array[j].Collider.AxisMax.y + 0.001;
                                    else if((Prefab_array[i].Collider.AxisMax.z - Prefab_array[j].Collider.AxisMin.z) < (Prefab_array[j].Collider.AxisMax.z - Prefab_array[i].Collider.AxisMin.z))
                                        Prefab_array[i].Position_Matrix[3][2] = Prefab_array[j].Collider.AxisMin.z- 0.001 - Prefab_array[i].Collider.Size_Z;
                                    else
                                        Prefab_array[i].Position_Matrix[3][2] = Prefab_array[j].Collider.AxisMax.z+ 0.001 + Prefab_array[i].Collider.Size_Z;
                                    Prefab_array[i].Velocity.z = 0.0f;
                                    break;
                                }

                 }
        }
            ticks = 1;
            passt = 0.0f;
    }
}


void Ms_Scene::ColisionAxis()
{

}

///CALLBACKS (CUZ USING 'C' LIB [GLFW])
void Ms_Scene::Key_UP(int K)
{
    Ms_Scene::keys[K] = true;
}

void Ms_Scene::Key_DOWN(int K)
{
     Ms_Scene::keys[K] = false;
}

void Ms_Scene::mouse(double x, double y)
{
    Camera.mouse_callback(x, y);
}
