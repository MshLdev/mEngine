#include <GLFW/glfw3.h>

class Ms_Timer
{
    public:
        Ms_Timer();
        GLfloat GetDeltaTime();
        GLfloat GetElapsed();
        void TimerUpdate();
        virtual ~Ms_Timer();

    protected:
    GLfloat deltaTime;	    ///Czas miêdzy aktualna a ostatni¹ klatk¹
    GLfloat lastFrame;  	///Czas Ostatniej Klatki
    GLfloat Elapsed;        ///nie wiem xd

    private:

};
