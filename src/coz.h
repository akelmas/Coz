#ifndef COZ_H_
#define COZ_H_

#include "gamelogic.h"
#include "controller.h"
#include "graphics.h"
class Controller;
class Coz{
    public:
        enum class MENU{
            MAIN,
            HELP,
            OPTIONS,
            GAME,
            GAMEOVER
        };
        MENU CurrentMenu()const;

        void setMenu(MENU target);

        void run(GameLogic &gamelogic,Graphics &graphics,Controller &controller) ;
    private:
        MENU currentMenu{MENU::MAIN};

};
#endif