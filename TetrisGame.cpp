#include "TetrisGame.h"
#include "RandomBox.h"
#include <time.h>

namespace restonce {

TetrisGame::TetrisGame()
{
    gameStatus = GameStatus::undo;
    winStatus = WinStatus::lose;
    rd.seed (time(NULL));
    for(int l=0; l<LINE; ++l) {
        for(int r=0; r<ROW; ++r) {
            maps[l][r] = false;
        }
    }
}

void TetrisGame::init ()
{
    for(int l=0; l<LINE; ++l) {
        for(int r=0; r<ROW; ++r) {
            maps[l][r] = false;
        }
    }
    gameStatus = GameStatus::undo;
    winStatus = WinStatus::lose;
    activebox = std::make_shared<RandomBox>(*this, rd);
    nextBox = std::make_shared<RandomBox>(*this, rd);
}

void TetrisGame::start ()
{
    if ( gameStatus == GameStatus::runing ) {
        throw std::logic_error("Game is runing !");
    }
    init();
    gameStatus = GameStatus::runing;
}

int TetrisGame::timeout ()
{
    int fullLine=0;

    if ( gameStatus != GameStatus::runing ) {
        return fullLine ;
    }
    if ( !activebox->down () ) {
        // 此处准备消行
        fullLine=0;
        for(int line=LINE-1; line>=0; --line) {
            bool isFull = true;
            for(int row=0; row<ROW; ++row) {
                if ( !this->exists (line, row) ) {
                    isFull = false;
                    break;
                }
            }
            if ( isFull ) {
                for(int l=line; l>=0; --l) {
                    for(int r=0; r<ROW; ++r) {
                        if ( l ==0 ) {
                            maps[l][r] = false;
                        } else {
                            maps[l][r] = maps[l-1][r];
                        }
                    }
                }
                ++ line;
                ++fullLine;
            }
        }
        //
        activebox =nextBox;
        nextBox=std::make_shared<RandomBox>(*this, rd);
        if ( !activebox->valid () ) { // 新产生的方块不合法，说明你已经输了
            gameStatus = GameStatus::stop;
            winStatus = WinStatus::lose;
        }
    }
    return fullLine;
}

bool TetrisGame::transform()
{
    return activebox->transform ();
}

int TetrisGame::down()
{
    return timeout ();
}

bool TetrisGame::left()
{
    return activebox->left ();
}

bool TetrisGame::right()
{
    return activebox->right ();
}

void TetrisGame::stop()
{
    if ( gameStatus == GameStatus::runing ) {
        gameStatus = GameStatus::stop;
        winStatus = WinStatus::lose;
    }
}

TetrisGame::GameStatus TetrisGame::getGameStatus () const
{
    return gameStatus;
}

TetrisGame::WinStatus TetrisGame::getWinStatus () const
{
    if ( gameStatus != GameStatus::stop ) {
        throw std::logic_error("Game is not stop !");
    }
    return winStatus;
}

bool TetrisGame::valid (int line, int row) const
{
    return line >=0 && line < LINE &&
            row >=0 && row < ROW;
}

bool TetrisGame::exists (int line, int row) const
{
    if ( !valid (line, row) ) {
        throw std::out_of_range("Game position not exists !");
    }
    return maps[line][row];
}

bool TetrisGame::inActiveBox(int line, int row) const
{
    if ( activebox ) {
        return activebox->inBody(line, row);
    }
    return false;
}

void TetrisGame::set (int line, int row)
{
    maps[line][row] = true;
}

std::shared_ptr<RandomBox> TetrisGame::getNextBox () const
{
    return nextBox;
}

} // namespace restonce
