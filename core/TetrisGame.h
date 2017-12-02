#ifndef RESTONCE_TETRISGAME_H
#define RESTONCE_TETRISGAME_H

#include <memory>
#include <random>
#include "Subject.h"

namespace restonce {

class RandomBox;

class TetrisGame
        : public Subject
{
public:
    enum class GameStatus {
        undo, runing, stop
    };
    enum class WinStatus {
        win, lose
    };
    enum {
        ROW = 10,
        LINE = 18
    };
    TetrisGame();
    // 用户通过gui可以对游戏进行的操作
    void start();
    void timeout();
    void transform();
    void down();
    void left();
    void right();
    void stop();
    // gui更新时会用以下函数读取游戏状态
    GameStatus getGameStatus() const;
    WinStatus getWinStatus() const;
    // 是否存在方块,如果越界会抛出异常
    bool exists(int line, int row) const;
    int color(int line, int row) const;
    std::shared_ptr<RandomBox> getActiveBox() const;
    // 下一个Box
    std::shared_ptr<RandomBox> getNextBox() const;
    // 某位置是否越界
    bool valid(int line, int row) const;
    // 填充某个位置
    void set(int line, int row, int color);
private:
    void init();

private:
    GameStatus m_gameStatus;
    WinStatus m_winStatus;
    bool m_map[LINE][ROW] ;
    int  m_colorMap[LINE][ROW] ;
    std::shared_ptr<RandomBox> m_activebox, m_nextBox;
    std::mt19937 m_rd;
};

} // namespace restonce

#endif // RESTONCE_TETRISGAME_H
