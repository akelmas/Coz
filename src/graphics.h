#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "definitions.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gamelogic.h"
#include <SDL_ttf.h>
#include <map>

class Graphics
{
public:
//constructor and destructor
    Graphics(GameLogic &gamelogic);
    ~Graphics();
    //Screen dimension constants


    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    //draws main
    bool drawMain();

    //draws options
    bool drawOptions();

    //draw game
    bool drawGame(GameLogic &gamelogic);

    //draw game over screen
    bool drawGameOver(GameLogic &gamelogic);


    //draws a screen, how to play
    bool drawHelp();
    
    //renders text 
    bool drawText(std::string text, int x,int y,SDL_Color color,int size);

    //draws an empty rect
    bool drawRect( int x,int y,int w, int h, int linewidth, SDL_Color color);

    //Frees media and shuts down SDL
    void close();


private:
    
    //The window we'll be rendering to
    SDL_Window* gWindow;
        
    //The surface contained by the window
    SDL_Surface* gScreenSurface;

    //The image we will load and show on the screen
    SDL_Texture *gBackgroundImage;
    SDL_Texture *gPieceWhiteImage;
    SDL_Texture *gPieceBlackImage;
    SDL_Texture *gHoleImage;
    SDL_Texture *gHelpImage;
    SDL_Renderer *gRenderer;
    //Globally used fonts
    std::map<int,TTF_Font*> gFonts;

    SDL_Texture* mTexture;
    SDL_Texture* textBgTexture;
    


};
#endif
