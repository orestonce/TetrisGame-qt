#ifndef RESTONCE_RANDOMBOX_H
#define RESTONCE_RANDOMBOX_H

#include <vector>
#include <random>

namespace restonce {
class TetrisGame;
class Point
{
public :
    Point(int line, int row);
    int line() const;
    int row() const;
    void setLine(int line);
    void setRow(int row);
private:
    int m_line, m_row;
};

class RandomBox
{
public:
    RandomBox(TetrisGame& game_, std::mt19937& rd);
    // 判断在自己的位置有方块占有
    bool valid();
    // 尝试旋转
    bool transform();
    bool down();
    bool left();
    bool right();
    // 判断某位置是否与自己冲突
    bool inBody(int line, int row) const;
    // 将自己填充到游戏地图上
    void set();
    int color() const;
    // 读取自己的所有方块
    std::vector<Point> getMyBoxes() const;
private:
    std::vector<Point> getNextBoxes(int line_inc, int row_inc) const;
    std::vector<Point> getNextBoxes() const;
private:
    TetrisGame& m_game;
    Point m_basicPosition; // 自己的左上角位置
    int m_boxpos; // 自己是box列表中的第几个
    int m_color;
};

} // namespace restonce

#endif // RESTONCE_RANDOMBOX_H
