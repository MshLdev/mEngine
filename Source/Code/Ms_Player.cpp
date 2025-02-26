#include "Ms_Player.h"

Ms_Player::Ms_Player()
{
    Ammo = 60;
    Mags = 3;
    Anim_id = 1;
    Anim_Timer = 0.0f;
    isAirborn = false;
    isShooting = false;
    FireRate = 0.5;
    ReloadRate = 3;
    SinceShoot = 0.0f;
    Gravity = -0.1;
    downtime = 0.0f;
}

Ms_Player::~Ms_Player()
{

}

glm::vec3 Ms_Player::Get_Pos(Ms_Prefab obj)
{
    return glm::vec3(obj.Position_Matrix[3][0], obj.Position_Matrix[3][1] + 2.0f , obj.Position_Matrix[3][2]);
}

void Ms_Player::Jump(bool keys[], float Delta)
{
    if(isAirborn && AirTime <= 0.165f)
        AirTime += Delta;
    else
    {
        isAirborn = false;
        AirTime = 0.0f;
    }

    if(keys[GLFW_KEY_SPACE] && !isAirborn && downtime <= 0.0f)
    {
        downtime = 0.5f;
        isAirborn = true;
    }

    if(isAirborn)
    {
         Gravity = 0.1;
    }
    else
        Gravity = -0.1;

    if(downtime > 0.0f)
         downtime -= Delta;
}

void Ms_Player::UseWeapon(bool keys[], float Delta)
{
    if(isShooting)
        isShooting = false;

    if(SinceShoot >= FireRate)
      {
        Anim_id = 1;

          if(!isShooting && keys[GLFW_KEY_1] && Ammo > 0)
            {
                Ammo -= 1;
                Anim_Timer = 0.0f;
                Anim_id = 2;
                isShooting = true;
                SinceShoot = 0.0f;
                std::cout<<"Shoot!"<<Delta<<"\n";
            }
      }


    SinceShoot += Delta;
}

glm::vec3 Ms_Player::Movement(Ms_Camera Camera, bool keys[500])
{
    glm::vec3 Ready_Movement(0.0f, Gravity, 0.0f);
    if(keys[GLFW_KEY_W])
        Ready_Movement += glm::vec3(Camera.Camera_2dVector.x*0.05, 0.0f, Camera.Camera_2dVector.z*0.05);
    if(keys[GLFW_KEY_S])
        Ready_Movement += glm::vec3(Camera.Camera_2dVector.x*-0.05, 0.0f, Camera.Camera_2dVector.z*-0.05);
    if(keys[GLFW_KEY_A])
        Ready_Movement += glm::vec3(Camera.CrossProd.x*-0.05, 0.0f, Camera.CrossProd.z*-0.05);
    if(keys[GLFW_KEY_D])
        Ready_Movement += glm::vec3(Camera.CrossProd.x*0.05, 0.0f, Camera.CrossProd.z*0.05);
    else
        return Ready_Movement;
}

glm::mat4 Ms_Player::Set_FPS_Matrix(Ms_Camera Camera)
{
    glm::mat4 rotation_Matrix = glm::inverse(glm::lookAt(Camera.GetPos(), Camera.GetPos() + Camera.GetFront(), glm::cross( Camera.CrossProd, Camera.cameraFront)));
    rotation_Matrix[3] = glm::vec4(Camera.cameraPos, 1.0f);
    return rotation_Matrix;
}
