#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "definitions.h"
#include <vector>


struct Point
{
    int x;
    int y;
};

class GameLogic
{

public:
    enum class State
    {
        EMPTY,
        BLACK,
        WHITE
    };
    enum class GameLevel
    {
        EASY,
        MODERATE,
        HARD
    };
    enum class Player
    {
        BLACK,
        WHITE
    };
    size_t Size();
    //getters/setters
    bool PlayerMoved()const;
    bool PieceSelected()const;
    void setLevel(GameLevel selected);

    Player CurrentPlayer()const;
    //returns true if all pieces have been placed
    bool allPiecesPlaced();
    int RemainingPiecesBlack()const;
    int RemainingPiecesWhite()const;

    //methods
    void togglePlayer();
    bool selectPiece(Point &p);
    bool selectTarget(Point &p);





    //init the game, resettin board
    void init();
    //returns the status of game: false for gameover
    bool isGameOver();

    State board[5][5];
    Point source,target;

private:
    Player currentPlayer;
    GameLevel level;
    size_t boardSize;
    bool pieceSelected;
    bool playerMoved;
    int remainingPiecesBlack;
    int remainingPiecesWhite;
    

};

#endif