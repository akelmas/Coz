#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "coz.h"
#include "gamelogic.h"

class Coz;
class Controller {
 public:
    void HandleInput(bool &running, GameLogic &gamelogic, Coz &coz) const;

 private:
    void MovePiece(GameLogic &gamelogic) const;
};

#endif