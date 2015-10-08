#ifndef RESTONCE_TETRISGAME_H
#define RESTONCE_TETRISGAME_H

#include <memory>
#include <random>

namespace restonce {

class RandomBox;

class TetrisGame
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
    void start();
    int timeout();
    bool transform();
    int down();
    bool left();
    bool right();
    void stop();
    GameStatus getGameStatus() const;
    WinStatus getWinStatus() const;
    // 是否存在方块,如果越界会抛出异常
    bool exists(int line, int row) const;
    bool inActiveBox(int line, int row) const;
    std::shared_ptr<RandomBox> getNextBox() const;
    // 内部使用
    // 是否越界
    bool valid(int line, int row) const;
    void set(int line, int row);
private:
    void init();

private:
    GameStatus gameStatus;
    WinStatus winStatus;
    bool maps[LINE][ROW] ;
    std::shared_ptr<RandomBox> activebox, nextBox;
    std::mt19937 rd;
};

} // namespace restonce

#endif // RESTONCE_TETRISGAME_H
