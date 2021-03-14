
#include "controller.h"
#include <iostream>
#include "SDL.h"
void Controller::HandleInput(bool &running, GameLogic &gamelogic, Coz &coz) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type==SDL_KEYDOWN)
    {
    
      
      switch (e.key.keysym.sym)
      {
      case SDLK_ESCAPE:
      //set ESC key to return main menu
        coz.setMenu(Coz::MENU::MAIN);
        break;
      case SDLK_h:
        coz.setMenu(Coz::MENU::HELP);
        break;
      default:
        break;
      }
    }
    
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      int x, y;
      SDL_GetMouseState(&x, &y);

      switch (coz.CurrentMenu())
      {
      case Coz::MENU::MAIN:
      { //check if start button is clicked
        //in main screen if a click occurs in button rect
        //button bounds x:100,y:300,w:280,h:110,
        if (x > 100 && x < 380 && y > 110 && y < 410)
        {
          //button clicked, move to next menu
          coz.setMenu(Coz::MENU::OPTIONS);
        }

        break;
      }
      case Coz::MENU::OPTIONS:
      { //three buttons here
        //user will choose difficulty level
        //options easy, moderate, hard
        bool isClicked = false;
        if (x > 100 && x < 380 && y > 240 && y < 300)
        {
          gamelogic.setLevel(GameLogic::GameLevel::EASY);
          isClicked = true;
        }
        else if (x > 100 && x < 380 && y > 320 && y < 380)
        {
          gamelogic.setLevel(GameLogic::GameLevel::MODERATE);
          isClicked = true;
        }
        else if (x > 100 && x < 380 && y > 400 && y < 460)
        {
          gamelogic.setLevel(GameLogic::GameLevel::HARD);
          isClicked = true;
        }
        if (isClicked)
        {
          gamelogic.init();
          coz.setMenu(Coz::MENU::GAME);
        }
        break;
      }
      case Coz::MENU::GAME:
      { //in game, two player will move sequently,
        //in the beginning of the round players will place their pieces one by one

        Point mousePos;
        mousePos.x = x;
        mousePos.y = y;

        if (!gamelogic.allPiecesPlaced() && gamelogic.selectTarget(mousePos))
        {
          printf("Piece placed!\n");
        }
        else
        {

          //after placement is done, game starts
          //in each move player turn will change
          //first, check the piece coordinates if clicked
          if (!gamelogic.PieceSelected())
          {
            if (gamelogic.selectPiece(mousePos))
            {
              //printf("%d\t\t%d\t\t%d\t\t%d\t\t%d  \n", gamelogic.PieceSelected(), gamelogic.source.x, gamelogic.source.y, gamelogic.target.x, gamelogic.target.y);
            }
          }
        }

        break;
      }
      case Coz::MENU::HELP:
      {
        //nothing to control here, just to avoid compile warning
        break;
      }
      case Coz::MENU::GAMEOVER:
      {
                //nothing to control here, just to avoid compile warning
        break;
      }

      }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
      if (gamelogic.PieceSelected())
      {
        if (coz.CurrentMenu() == Coz::MENU::GAME)
        {
          int x, y;
          SDL_GetMouseState(&x, &y);
          Point mousePos;
          mousePos.x = x;
          mousePos.y = y;
          if (gamelogic.selectTarget(mousePos))
          {
            //printf("%d\t\t%d\t\t%d\t\t%d\t\t%d  \n", gamelogic.PieceSelected(), gamelogic.source.x, gamelogic.source.y, gamelogic.target.x, gamelogic.target.y);
            MovePiece(gamelogic);
            if (gamelogic.isGameOver()) 
            {
              coz.setMenu(Coz::MENU::GAMEOVER);
            }
            
            gamelogic.togglePlayer();
          }
        }
      }
    }
  }
}
void Controller::MovePiece(GameLogic &gamelogic) const
{
  GameLogic::State sourceState = gamelogic.board[gamelogic.source.y][gamelogic.source.x];
  gamelogic.board[gamelogic.source.y][gamelogic.source.x] = GameLogic::State::EMPTY;
  gamelogic.board[gamelogic.target.y][gamelogic.target.x] = sourceState;
}