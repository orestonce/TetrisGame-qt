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
    int line_, row_;
};

class RandomBox
{
public:
    RandomBox(TetrisGame& game_, std::mt19937& rd);
    bool valid(); // 判断在自己的位置有方块占有
    bool transform();
    bool down();
    bool left();
    bool right();
    bool inBody(int line, int row) const;
    void set();
    std::vector<Point> getMyBoxes() const;
private:
    std::vector<Point> getNextBoxes(int line_inc, int row_inc) const;
    std::vector<Point> getNextBoxes() const;
private:
    TetrisGame& game;
    Point basicPosition;
    int boxpos;
};

} // namespace restonce

#endif // RESTONCE_RANDOMBOX_H
