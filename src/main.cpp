#include "coz.h"


int main( int argc, char* args[] )
{	Coz game;
	GameLogic gamelogic;
	Graphics graphics(gamelogic);
	Controller controller;
	
	game.run(gamelogic,graphics,controller);

	return 0;
}
