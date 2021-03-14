

#include "gamelogic.h"
#include <random>

void GameLogic::init()
{
    switch (level)
    {
    case GameLevel::EASY:
        boardSize = 3;
        break;
    case GameLevel::MODERATE:
        boardSize = 4;
        break;
    case GameLevel::HARD:
        boardSize = 5;
        break;
    default:
        boardSize = 3;
        break;
    }

    //create an empty board
    for (size_t i = 0; i < boardSize; i++)
    {

        for (size_t j = 0; j < boardSize; j++)
        {
            board[i][j] = State::EMPTY;
        }
    }
    remainingPiecesBlack = remainingPiecesWhite = boardSize;
    playerMoved = false;
    //randomly determine the first player
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution distribution(0.5);
    bool drawFirstPlayer = distribution(gen);
    currentPlayer = drawFirstPlayer ? GameLogic::Player::BLACK : GameLogic::Player::WHITE;
    pieceSelected = false;
}

bool GameLogic::PlayerMoved() const
{
    return playerMoved;
}

int GameLogic::RemainingPiecesBlack() const { return remainingPiecesBlack; }
int GameLogic::RemainingPiecesWhite() const { return remainingPiecesWhite; }

GameLogic::Player GameLogic::CurrentPlayer() const { return currentPlayer; }

bool GameLogic::isGameOver()
{
    //search for game over

    //check rows and columns
    for (size_t i = 0; i < boardSize; i++)
    {
        State firstOfRow = board[i][0];
        State firstOfColumn = board[0][i];
        size_t rowCounter = 0;
        size_t columnCounter = 0;
        for (size_t j = 0; j < boardSize; j++)
        {
            if (board[i][j] == firstOfRow && board[i][j] != State::EMPTY)
            {
                rowCounter++;
            }
            if (board[j][i] == firstOfColumn && board[j][i] != State::EMPTY)
            {
                columnCounter++;
            }
        }

        if (rowCounter == boardSize || columnCounter == boardSize)
        {
            return true;
        }
    }

    //check diagonals

    State firstOfDiagonal1 = board[0][0];

    State firstOfDiagonal2 = board[0][boardSize - 1];
     size_t diagonal1Counter = 0;
    size_t diagonal2Counter = 0;
    for (size_t i = 0; i < boardSize; i++)
    {

       

        if (board[i][i] == firstOfDiagonal1 && board[i][i] != State::EMPTY)
        {
            diagonal1Counter++;
        }
        if (board[i][boardSize - 1 - i] == firstOfDiagonal2 && board[i][boardSize - 1 - i] != State::EMPTY)
        {
            diagonal2Counter++;
        }
        if (diagonal1Counter == boardSize || diagonal2Counter == boardSize)
        {
            return true;
        }
    }

    return false;
}

size_t GameLogic::Size()
{
    return boardSize;
}

void GameLogic::setLevel(GameLogic::GameLevel selected)
{
    level = selected;
}

void GameLogic::togglePlayer()
{
    currentPlayer = (currentPlayer == Player::BLACK) ? Player::WHITE : Player::BLACK;
    playerMoved = true;
}
bool GameLogic::selectPiece(Point &p)
{
    if (!allPiecesPlaced())
    {
        return true;
    }

    //convert coordinates to board indexes
    int gridX, gridY;

    gridX = (p.x - BOARD_OFFSET) / ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize);
    gridY = (p.y - BOARD_OFFSET) / ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize);
    //check if point is in range
    if (gridX >= 0 && gridX < boardSize && gridY >= 0 && gridY < boardSize)
    {
        //check if it is a valid click

        //find center of clickable area

        int centerX, centerY, r;
        r = ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize - BOARD_OFFSET) / 2;
        centerX = BOARD_OFFSET + gridX * (SCREEN_WIDTH - BOARD_OFFSET) / boardSize + r;
        centerY = BOARD_OFFSET + gridY * (SCREEN_WIDTH - BOARD_OFFSET) / boardSize + r;

        //check if click is inside the circle

        if (r * r > (pow(centerX - p.x, 2) + pow(centerY - p.y, 2)))
        {
            if (board[gridY][gridX] != State::EMPTY)
            {
                pieceSelected = true;
                if (currentPlayer == Player::BLACK && board[gridY][gridX] == State::BLACK)
                {
                    source.x = gridX;
                    source.y = gridY;
                    return true;
                }
                else if (currentPlayer == Player::WHITE && board[gridY][gridX] == State::WHITE)
                {
                    source.x = gridX;
                    source.y = gridY;
                    return true;
                }
            }
        }
        pieceSelected = false;
    }
    source.x = source.y = -1;
    return false;
}
bool GameLogic::selectTarget(Point &p)
{

    //convert coordinates to board indexes
    int gridX, gridY;

    gridX = (p.x - BOARD_OFFSET) / ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize);
    gridY = (p.y - BOARD_OFFSET) / ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize);
    //check if point is in range
    if (gridX >= 0 && gridX < boardSize && gridY >= 0 && gridY < boardSize)
    {
        //check if it is a valid click

        //find center of clickable area

        int centerX, centerY, r;
        r = ((SCREEN_WIDTH - BOARD_OFFSET) / boardSize - BOARD_OFFSET) / 2;
        centerX = BOARD_OFFSET + gridX * (SCREEN_WIDTH - BOARD_OFFSET) / boardSize + r;
        centerY = BOARD_OFFSET + gridY * (SCREEN_WIDTH - BOARD_OFFSET) / boardSize + r;

        //check if click is inside the circle

        if (r * r > (pow(centerX - p.x, 2) + pow(centerY - p.y, 2)))
        {

            if (!allPiecesPlaced())
            {
                //check if player attempts to make a shortcut to game end.
                //during placement, the final move is blocked
                State currentState = board[gridY][gridX];

                if (currentPlayer == Player::BLACK && board[gridY][gridX] == State::EMPTY)
                {
                    board[gridY][gridX] = State::BLACK;
                    remainingPiecesBlack--;
                }
                else
                {
                    board[gridY][gridX] = State::WHITE;
                    remainingPiecesWhite--;
                }

                if (isGameOver())
                {
                    //undo the move
                    printf("gameover\n");
                    board[gridY][gridX] = currentState;
                    if (currentPlayer == Player::BLACK)
                    {
                        remainingPiecesBlack++;
                    }
                    else
                    {
                        remainingPiecesWhite++;
                    }
                }
                else
                {
                    playerMoved = true;
                    togglePlayer();
                }

                return true;
            }
            else
            {
                //calculate manhattan distance between source and target
                int diff = abs(gridX - source.x) + abs(gridY - source.y);
                if (diff == 1)
                {
                    if (board[gridY][gridX] == State::EMPTY)
                    {
                        target.x = gridX;
                        target.y = gridY;
                        pieceSelected = false;
                        return true;
                    }
                }
            }
        }
    }
    pieceSelected = false;
    target.x = target.y = -1;
    return false;
}

bool GameLogic::allPiecesPlaced()
{
    return !(remainingPiecesBlack + remainingPiecesWhite);
}

bool GameLogic::PieceSelected() const
{
    return pieceSelected;
}
