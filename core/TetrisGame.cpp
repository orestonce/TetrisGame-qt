#include "TetrisGame.h"
#include "RandomBox.h"
#include <time.h>

namespace restonce {

TetrisGame::TetrisGame()
{
    m_gameStatus = GameStatus::undo;
    m_winStatus = WinStatus::lose;
    m_rd.seed(time(NULL));
    for(int l=0; l<LINE; ++l) {
        for(int r=0; r<ROW; ++r) {
            m_map[l][r] = false;
        }
    }
}

void TetrisGame::init()
{
    for(int l=0; l<LINE; ++l) {
        for(int r=0; r<ROW; ++r) {
            m_map[l][r] = false;
            m_colorMap[l][r] = 0;
        }
    }
    m_gameStatus = GameStatus::undo;
    m_winStatus = WinStatus::lose;
    m_activebox = std::make_shared<RandomBox>(*this, m_rd);
    m_nextBox = std::make_shared<RandomBox>(*this, m_rd);
}

void TetrisGame::start()
{
    if(m_gameStatus == GameStatus::runing) {
        throw std::logic_error("Game is runing !");
    }
    init();
    m_gameStatus = GameStatus::runing;
    notifyObservers();
}

void TetrisGame::timeout()
{
    if(m_gameStatus != GameStatus::runing) {
        return  ;
    }
    if(!m_activebox->down()) {
        // 此处准备消行
        for(int line=LINE-1; line>=0; --line) {
            bool isFull = true;
            for(int row=0; row<ROW; ++row) {
                if(!this->exists(line, row)) {
                    isFull = false;
                    break;
                }
            }
            if(isFull) {
                for(int l=line; l>=0; --l) {
                    for(int r=0; r<ROW; ++r) {
                        if(l ==0) {
                            m_map[l][r] = false;
                        } else {
                            m_map[l][r] = m_map[l-1][r];
                        }
                    }
                }
                ++ line;
            }
        }
        //
        m_activebox =m_nextBox;
        m_nextBox=std::make_shared<RandomBox>(*this, m_rd);
        if(!m_activebox->valid()) {
            // 新产生的方块不合法，说明你已经输了
            m_gameStatus = GameStatus::stop;
            m_winStatus = WinStatus::lose;
        }
    }
    notifyObservers();
}

void TetrisGame::transform()
{
    if(m_activebox->transform()) {
        notifyObservers();
    }
}

void TetrisGame::down()
{
    timeout();
}

void TetrisGame::left()
{
    if(m_activebox->left()) {
        notifyObservers();
    }
}

void TetrisGame::right()
{
    if(m_activebox->right()) {
        notifyObservers();
    }
}

void TetrisGame::stop()
{
    if(m_gameStatus == GameStatus::runing) {
        m_gameStatus = GameStatus::stop;
        m_winStatus = WinStatus::lose;
        notifyObservers();
    }
}

TetrisGame::GameStatus TetrisGame::getGameStatus() const
{
    return m_gameStatus;
}

TetrisGame::WinStatus TetrisGame::getWinStatus() const
{
    if(m_gameStatus != GameStatus::stop) {
        throw std::logic_error("Game is not stop !");
    }
    return m_winStatus;
}

bool TetrisGame::valid(int line, int row) const
{
    return line >=0 && line < LINE &&
            row >=0 && row < ROW;
}

bool TetrisGame::exists(int line, int row) const
{
    if(!valid(line, row)) {
        throw std::out_of_range("Game position not exists !");
    }
    return m_map[line][row];
}

int TetrisGame::color(int line, int row) const
{
    return m_colorMap[line][row];
}

std::shared_ptr<RandomBox> TetrisGame::getActiveBox() const
{
    return m_activebox;
}

void TetrisGame::set(int line, int row, int color)
{
    m_map[line][row] = true;
    m_colorMap[line][row] = color;
}

std::shared_ptr<RandomBox> TetrisGame::getNextBox() const
{
    return m_nextBox;
}

} // namespace restonce
