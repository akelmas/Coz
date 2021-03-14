#include <iostream>
#include "graphics.h"

Graphics::Graphics(GameLogic &gamelogic)
{
	//invalidate variables
	gWindow = NULL;
	gScreenSurface = NULL;
	gBackgroundImage = NULL;
	gPieceWhiteImage = NULL;
	gPieceBlackImage = NULL;
	gHoleImage = NULL;
	mTexture = NULL;
	textBgTexture = NULL;

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			printf("Succeeded to load media!\n");
		}
	}
}

Graphics::~Graphics()
{
	close();
}

bool Graphics::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("COZ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (nullptr == gRenderer)
			{
				std::cerr << "Renderer could not be created.\n";
				std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
			}
		}
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}

bool Graphics::loadMedia()
{
	int w, h; // texture width & height
	//Loading success flag
	bool success = true;

	//Load fonts
	for (size_t i = 1; i < 160; i++)
	{
		gFonts[i] = TTF_OpenFont("../data/ShortBaby-Mg2w.ttf", i);
		if (gFonts[i] == NULL)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
	}

	//Load splash image
	gBackgroundImage = IMG_LoadTexture(gRenderer, "../data/bg.png");
	SDL_QueryTexture(gBackgroundImage, NULL, NULL, &w, &h);
	if (gBackgroundImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "data/bg.png", SDL_GetError());
		success = false;
	}
	gPieceWhiteImage = IMG_LoadTexture(gRenderer, "../data/white.png");
	SDL_QueryTexture(gPieceWhiteImage, NULL, NULL, &w, &h);
	if (gPieceWhiteImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "data/white.png", SDL_GetError());
		success = false;
	}

	gPieceBlackImage = IMG_LoadTexture(gRenderer, "../data/black.png");
	SDL_QueryTexture(gPieceBlackImage, NULL, NULL, &w, &h);
	if (gPieceBlackImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "data/black.png", SDL_GetError());
		success = false;
	}
	gHoleImage = IMG_LoadTexture(gRenderer, "../data/hole.png");
	SDL_QueryTexture(gHoleImage, NULL, NULL, &w, &h);
	if (gHoleImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "data/hole.png", SDL_GetError());
		success = false;
	}

	gHelpImage = IMG_LoadTexture(gRenderer, "../data/help.png");
	SDL_QueryTexture(gHelpImage, NULL, NULL, &w, &h);
	if (gHelpImage == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "data/help.png", SDL_GetError());
		success = false;
	}


	return success;
}

//draws main
bool Graphics::drawMain()
{

	//draw background
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(gRenderer, gBackgroundImage, NULL, &rect);

	drawText("COZ", 75, 43, {0x02, 0x30, 0x47}, 155);

	drawRect(100, 300, 280, 110, 5, {0xEA, 0xE2, 0xB7});

	drawText("Start", 165, 325, {0xEA, 0xE2, 0xB7}, 62);

	drawText("Press H for help :)", 150, 430, {0x02, 0x30, 0x47}, 24);

	SDL_RenderPresent(gRenderer);
	return true;
}

//draws help
bool Graphics::drawHelp()
{

	//draw background
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(gRenderer, gHelpImage, NULL, &rect);

	SDL_RenderPresent(gRenderer);
	return true;
}

//draws options
bool Graphics::drawOptions()
{
	//draw background
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(gRenderer, gBackgroundImage, NULL, &rect);

	drawText("COZ", 75, 43, {0x02, 0x30, 0x47}, 155);

	//easy
	drawRect(100, 240, 280, 60, 5, {0xEA, 0xE2, 0xB7});
	drawText("Easy", 110, 252, {0xEA, 0xE2, 0xB7}, 36);

	//moderate
	drawRect(100, 320, 280, 60, 5, {0xEA, 0xE2, 0xB7});
	drawText("Moderate", 110, 332, {0xEA, 0xE2, 0xB7}, 36);

	//hard
	drawRect(100, 400, 280, 60, 5, {0xEA, 0xE2, 0xB7});
	drawText("Hard", 110, 412, {0xEA, 0xE2, 0xB7}, 36);

	SDL_RenderPresent(gRenderer);
	return true;
}

//draw game
bool Graphics::drawGame(GameLogic &gamelogic)
{

	//draw background
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(gRenderer, gBackgroundImage, NULL, &rect);

	if (!gamelogic.allPiecesPlaced())
	{
		//remaining pieces
		for (int i = 0; i < gamelogic.RemainingPiecesBlack(); i++)
		{
			rect.h = BOARD_OFFSET / 2;
			rect.w = rect.h;
			rect.x = BOARD_OFFSET / 2 + i * rect.w;
			rect.y = BOARD_OFFSET / 4;
			SDL_RenderCopy(gRenderer, gPieceBlackImage, NULL, &rect);
		}

		//remaining pieces
		for (int i = 0; i < gamelogic.RemainingPiecesWhite(); i++)
		{
			rect.h = BOARD_OFFSET / 2;
			rect.w = rect.h;
			rect.x = SCREEN_WIDTH - ((i + 1) * rect.w + BOARD_OFFSET / 2);
			rect.y = BOARD_OFFSET / 4;
			SDL_RenderCopy(gRenderer, gPieceWhiteImage, NULL, &rect);
		}
	}

	//draw current player indicator
	rect.h = 3 * BOARD_OFFSET / 4;
	rect.w = rect.h;
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = BOARD_OFFSET / 8;
	if (gamelogic.CurrentPlayer() == GameLogic::Player::BLACK)
	{

		SDL_RenderCopy(gRenderer, gPieceBlackImage, NULL, &rect);
	}
	else
	{
		SDL_RenderCopy(gRenderer, gPieceWhiteImage, NULL, &rect);
	}

	//draw grid
	for (size_t i = 0; i < gamelogic.Size(); i++)
	{

		int x1 = BOARD_OFFSET + (((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET) / 2;
		int x2 = SCREEN_WIDTH - x1;
		int y1 = BOARD_OFFSET + i * ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) + (((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET) / 2;
		int y2 = y1;

		//printf("line H:%lu\tx1: %d\ty1:%d\tx2:%d\ty2:%d\n", i + 1, x1, y1, x2, y2);

		//a horizontal line
		SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);

		//printf("line V:%lu\tx1: %d\ty1:%d\tx2:%d\ty2:%d\n", i + 1, y1, x1, y2, x2);
		//a vertical line

		SDL_RenderDrawLine(gRenderer, y1, x1, y2, x2);
	}

	//draw holes
	for (size_t i = 0; i < gamelogic.Size(); i++)
	{
		for (size_t j = 0; j < gamelogic.Size(); j++)
		{
			//calculate piece position over grid area
			SDL_Rect rect;
			rect.w = ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
			rect.h = ((SCREEN_HEIGHT - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
			rect.x = BOARD_OFFSET + j * ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size());
			rect.y = BOARD_OFFSET + i * ((SCREEN_HEIGHT - BOARD_OFFSET) / gamelogic.Size());
			SDL_RenderCopy(gRenderer, gHoleImage, NULL, &rect);
		}
	}


	//draw pieces through board
	//relatively, black and white pieces are drawn in the same way
	for (size_t i = 0; i < gamelogic.Size(); i++)
	{
		for (size_t j = 0; j < gamelogic.Size(); j++)
		{
			//calculate piece position over grid area
			SDL_Rect rect;
			rect.w = ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
			rect.h = ((SCREEN_HEIGHT - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
			rect.x = BOARD_OFFSET + j * ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size());
			rect.y = BOARD_OFFSET + i * ((SCREEN_HEIGHT - BOARD_OFFSET) / gamelogic.Size());
			if (!(i == gamelogic.source.y && j == gamelogic.source.x && gamelogic.PieceSelected())) //do not draw selected piece
			{
				switch (gamelogic.board[i][j])
				{
				case GameLogic::State::BLACK:
					SDL_RenderCopy(gRenderer, gPieceBlackImage, NULL, &rect);
					break;
				case GameLogic::State::WHITE:
					SDL_RenderCopy(gRenderer, gPieceWhiteImage, NULL, &rect);
					break;
				default:
					break;
				}
			}
		}
	}

	if (gamelogic.PieceSelected())
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		//calculate piece position over grid area
		SDL_Rect rect;
		rect.w = ((SCREEN_WIDTH - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
		rect.h = ((SCREEN_HEIGHT - BOARD_OFFSET) / gamelogic.Size()) - BOARD_OFFSET;
		rect.x = mouseX - rect.w / 2;
		rect.y = mouseY - rect.h / 2;
		switch (gamelogic.board[gamelogic.source.y][gamelogic.source.x])
		{
		case GameLogic::State::BLACK:
			SDL_RenderCopy(gRenderer, gPieceBlackImage, NULL, &rect);
			break;
		case GameLogic::State::WHITE:
			SDL_RenderCopy(gRenderer, gPieceWhiteImage, NULL, &rect);
			break;
		default:
			break;
		}
	}

	SDL_RenderPresent(gRenderer);
	return true;
}

void Graphics::close()
{
	//Deallocate textures
	SDL_DestroyTexture(gBackgroundImage);
	SDL_DestroyTexture(gPieceBlackImage);
	SDL_DestroyTexture(gPieceWhiteImage);
	SDL_DestroyTexture(gHoleImage);
	SDL_DestroyTexture(gHelpImage);
	SDL_DestroyTexture(mTexture);
	SDL_DestroyTexture(textBgTexture);
	gBackgroundImage = NULL;
	gPieceWhiteImage = NULL;
	gPieceBlackImage = NULL;
	gHelpImage=NULL;
	gHoleImage = NULL;
	gFonts.clear();

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool Graphics::drawText(std::string text, int x, int y, SDL_Color color, int size)
{

	//Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFonts[size], text.c_str(), color);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{

		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			SDL_Rect placeholder;
			placeholder.x = x;
			placeholder.y = y;
			placeholder.w = textSurface->w;
			placeholder.h = textSurface->h;

			SDL_RenderCopy(gRenderer, mTexture, NULL, &placeholder);
		}

		//Get rid of old surface
		//SDL_FreeSurface( textSurface );
	}
	return true;
}
bool Graphics::drawRect(int x, int y, int w, int h, int linewidth, SDL_Color color)
{
	SDL_Rect placeholder;
	placeholder.x = x;
	placeholder.y = y;
	placeholder.w = w;
	placeholder.h = h;

	/* Filling the surface with red color. */
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(gRenderer, &placeholder);

	//draw background of text and emulate stroke
	placeholder.x += linewidth;
	placeholder.y += linewidth;
	placeholder.w -= 2 * linewidth;
	placeholder.h -= 2 * linewidth;

	//draw background texture, it seems transparent :)
	SDL_RenderCopy(gRenderer, gBackgroundImage, &placeholder, &placeholder);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);

	return true;
}


bool Graphics::drawGameOver(GameLogic &gamelogic){
		//draw background
	SDL_Rect rect;
	rect.h = SCREEN_HEIGHT;
	rect.w = SCREEN_WIDTH;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(gRenderer, gBackgroundImage, NULL, &rect);
	//draw logo
	drawText("COZ", 75, 43, {0x02, 0x30, 0x47}, 155);
	//draw winner indicator


	drawRect(100, 300, 280, 110, 5, {0xEA, 0xE2, 0xB7});

	//place player icon 
	rect.h = 80;
	rect.w = 80;
	rect.x = 110;
	rect.y = 310;

	SDL_RenderCopy(gRenderer,gamelogic.CurrentPlayer()!=GameLogic::Player::BLACK?gPieceBlackImage:gPieceWhiteImage,NULL,&rect);

	drawText("WON!", 200, 325, {0xEA, 0xE2, 0xB7}, 62);

	drawText("Press ESC to return main menu", 75, 430, {0x02, 0x30, 0x47}, 24);

	SDL_RenderPresent(gRenderer);
	return true;
}