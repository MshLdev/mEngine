#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ms_Prefab.h"
#include "Ms_Camera.h"

class Ms_Player
{
    public:
        Ms_Player();
        glm::vec3 Get_Pos(Ms_Prefab Body);
        glm::vec3 Movement(Ms_Camera Camera, bool keys[500]);
        glm::mat4 Set_FPS_Matrix(Ms_Camera Camera);
        void Jump(bool keys[], float Delta);
        void UseWeapon(bool keys[], float Delta);

        virtual ~Ms_Player();

        int Wep_id;
        int Anim_id;
        int Body_id;

        int Ammo;
        int Mags;

        float Gravity;
        float AirTime;
        float downtime;
        float ReloadRate;
        float FireRate;
        float SinceShoot;
        float Anim_Timer;

        bool isAirborn;
        bool isShooting;



    protected:

    private:

};
