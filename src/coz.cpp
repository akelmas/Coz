

#include <SDL.h>
#include "coz.h"

Coz::MENU Coz::CurrentMenu() const
{
  return currentMenu;
}

void Coz::setMenu(Coz::MENU target)
{
  currentMenu = target;
}

void Coz::run(GameLogic &gamelogic, Graphics &graphics, Controller &controller)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  bool running = true;
  bool gamestarted = false;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, gamelogic, *this);

    switch (currentMenu)
    {
    case MENU::MAIN:
      graphics.drawMain();

      break;
    case MENU::OPTIONS:
      graphics.drawOptions();
      break;
    case MENU::GAME:
     graphics.drawGame(gamelogic);
     break;
    case MENU::GAMEOVER:
      graphics.drawGameOver(gamelogic);
      break;
    case MENU::HELP:
      graphics.drawHelp();
      break;
    default:
      break;
    }

    frame_end = SDL_GetTicks();
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    frame_duration = frame_end - frame_start;
    if (frame_duration < 30)
    {
      SDL_Delay(30 - frame_duration);
    }
  }
}
