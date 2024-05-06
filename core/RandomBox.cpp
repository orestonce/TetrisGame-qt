#include "RandomBox.h"
#include "TetrisGame.h"

namespace restonce {

Point::Point(int line, int row)
    : m_line(line), m_row(row)
{

}
int Point::line() const
{
    return m_line;
}
int Point::row() const
{
    return m_row;
}
void Point::setLine(int line)
{
    m_line = line;
}
void Point::setRow(int row)
{
    m_row = row;
}

struct Box {
    Point boxes[4];
    int next;
} ;
static Box dbs[] = {
// * *
//   *
//   *
//
{{{0, 0}, {1, 0}, {1, 1}, {1, 2}},1},// 0, L
{{{2, 0}, {0, 1}, {1, 1}, {2, 1}},2},
{{{1, 0}, {1, 1}, {1, 2}, {2, 2}},3},
{{{0, 1}, {1, 1}, {2, 1}, {0, 2}},0},
//  * *
//  *
//  *
//
{{{1, 0}, {2, 0}, {1, 1}, {1, 2}},5},// 4, 反 L
{{{0, 1}, {1, 1}, {2, 1}, {2, 2}},6},
{{{1, 0}, {1, 1}, {0, 2}, {1, 2}},7},
{{{0, 0}, {0, 1}, {1, 1}, {2, 1}},4},
//    *
//    *
//    *
//    *
{{{1, 0}, {1, 1}, {1, 2}, {1, 3}},9}, // 8, --
{{{0, 1}, {1, 1}, {2, 1}, {3, 1}},8},
// * *
//   * *
//
//
{{{0, 0}, {1, 0}, {1, 1}, {2, 1}},11}, // 10, 反z
{{{2, 0}, {1, 1}, {2, 1}, {1, 2}},10},
//   * *
// * *
//
//
{{{1, 0}, {2, 0}, {0, 1}, {1, 1}},13}, // 12, z
{{{1, 0}, {1, 1}, {2, 1}, {2, 2}},12},
 // * *
 // * *
 //
 //
{{{0, 0}, {1, 0}, {0, 1}, {1, 1}},14}, // 14
//   *
// * * *
//
//
{{{1, 0}, {0, 1}, {1, 1}, {2, 1}},16}, // 15
{{{0, 0}, {0, 1}, {1, 1}, {0, 2}},17},
{{{0, 0}, {1, 0}, {2, 0}, {1, 1}},18},
{{{1, 0}, {0, 1}, {1, 1}, {1, 2}},15},
};

RandomBox::RandomBox(TetrisGame &game_, std::mt19937 &rd)
    : m_game(game_), m_basicPosition(0, 3)
{
    m_boxpos = rd() % (sizeof(dbs)/sizeof(dbs[0]));
    m_color = 1 +(rd() % 17);
}

bool RandomBox::valid()
{
    for(Point const& p: getMyBoxes()) {
        if(!m_game.valid(p.line(), p.row()) ||
             m_game.exists(p.line(), p.row())) {
            return false;
        }
    }
    return true;
}

bool RandomBox::down()
{
    for(Point const& p : getNextBoxes(1, 0)) {
        if(!m_game.valid(p.line(), p.row()) ||
             m_game.exists(p.line(), p.row())) {
            this->set();
            return false;
        }
    }
    m_basicPosition.setLine(m_basicPosition.line() +1);
    return true;
}

bool RandomBox::left()
{
    for(Point const& p : getNextBoxes(0, -1)) {
        if(!m_game.valid(p.line(), p.row()) ||
             m_game.exists(p.line(), p.row())) {
            return false;
        }
    }
    m_basicPosition.setRow(m_basicPosition.row() -1);
    return true;
}

bool RandomBox::right()
{
    for(Point const& p : getNextBoxes(0, 1)) {
        if(!m_game.valid(p.line(), p.row()) ||
             m_game.exists(p.line(), p.row())) {
            return false;
        }
    }
    m_basicPosition.setRow(m_basicPosition.row()+1);
    return true;
}

bool RandomBox::transform()
{
    for(Point const& p : getNextBoxes()) {
        if(!m_game.valid(p.line(), p.row()) ||
             m_game.exists(p.line(), p.row())) {
            return false;
        }
    }
    m_boxpos = dbs[m_boxpos].next;
    return true;
}

std::vector<Point> RandomBox::getMyBoxes() const
{
    std::vector<Point> mypoints;

    for(Point const& p : dbs[m_boxpos].boxes) {
        mypoints.push_back(Point(m_basicPosition.line() +p.line(),
                                  m_basicPosition.row() + p.row()));
    }
    return mypoints;
}

std::vector<Point> RandomBox::getNextBoxes(int line_inc, int row_inc) const
{
    std::vector<Point> nextBoxes;

    for(Point const& p : getMyBoxes()) {
        nextBoxes.push_back(Point(p.line()+line_inc, p.row() + row_inc));
    }
    return nextBoxes;
}

std::vector<Point> RandomBox::getNextBoxes() const
{
    std::vector<Point> nextBoxes;

    for(Point const& p : dbs[ dbs[m_boxpos].next ].boxes) {
        nextBoxes.push_back(Point(p.line()+m_basicPosition.line(),
                                   p.row() + m_basicPosition.row()));
    }
    return nextBoxes;
}

void RandomBox::set()
{
    for(Point const& p : getMyBoxes()) {
        m_game.set(p.line(), p.row(), m_color);
    }
}

int RandomBox::color() const
{
    return m_color;
}

bool RandomBox::inBody(int line, int row) const
{
    for(Point const& p : getMyBoxes()) {
        if(p.line() == line && p.row() == row) {
            return true;
        }
    }
    return false;
}

} // namespace restonce
