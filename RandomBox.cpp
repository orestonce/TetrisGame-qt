#include "RandomBox.h"
#include "TetrisGame.h"

namespace restonce {

Point::Point(int line, int row)
    : line_(line), row_(row)
{

}
int Point::line () const
{
    return line_;
}
int Point::row () const
{
    return row_;
}
void Point::setLine (int line)
{
    line_ = line;
}
void Point::setRow (int row)
{
    row_ = row;
}

struct Box {
    Point boxes[4];
    int next;
} ;
static Box dbs[] = {
//  * *
//     *
//     *
//
{{{0, 0}, {1, 0}, {1, 1}, {1, 2}},1},// L
{{{2, 0}, {0, 1}, {1, 1}, {2, 1}},2},
{{{1, 0}, {1, 1}, {1, 2}, {2, 2}},3},
{{{0, 1}, {1, 1}, {2, 1}, {0, 2}},0},
//  * *
//  *
//  *
//
{{{1, 0}, {2, 0}, {1, 1}, {1, 2}},5},// 反 L
{{{0, 1}, {1, 1}, {2, 1}, {2, 2}},6},
{{{1, 0}, {1, 1}, {0, 2}, {1, 2}},7},
{{{0, 0}, {0, 1}, {1, 1}, {2, 1}},4},
//    *
//    *
//    *
//    *
{{{1, 0}, {1, 1}, {1, 2}, {1, 3}},9}, // --
{{{0, 1}, {1, 1}, {2, 1}, {3, 1}},10},
{{{1, 0}, {1, 1}, {1, 2}, {1, 3}},11},
{{{0, 1}, {1, 1}, {2, 1}, {3, 1}},8},
// *  *
//     *  *
//
//
{{{0, 0}, {1, 0}, {1, 1}, {2, 1}},13}, // 12
{{{2, 0}, {1, 1}, {2, 1}, {1, 2}},14},
{{{0, 0}, {1, 0}, {1, 1}, {2, 1}},15},
{{{2, 0}, {1, 1}, {2, 1}, {1, 2}},12},
//    *  *
// * *
//
//
{{{1, 0}, {2, 0}, {0, 1}, {1, 1}},17}, // 16
{{{1, 0}, {1, 1}, {2, 1}, {2, 2}},18},
{{{1, 0}, {2, 0}, {0, 1}, {1, 1}},19},
{{{1, 0}, {1, 1}, {2, 1}, {2, 2}},16},
 // * *
 // * *
 //
 //
{{{0, 0}, {1, 0}, {0, 1}, {1, 1}},21},// 20
{{{0, 0}, {1, 0}, {0, 1}, {1, 1}},22},
{{{0, 0}, {1, 0}, {0, 1}, {1, 1}},23},
{{{0, 0}, {1, 0}, {0, 1}, {1, 1}},20},
//    *
// * * *
//
//
{{{1, 0}, {0, 1}, {1, 1}, {2, 1}},25}, // 24
{{{0, 0}, {0, 1}, {1, 1}, {0, 2}},26},
{{{0, 0}, {1, 0}, {2, 0}, {1, 1}},27},
{{{1, 0}, {0, 1}, {1, 1}, {1, 2}},24},
};

RandomBox::RandomBox(TetrisGame &game_, std::mt19937 &rd)
    : game(game_), basicPosition(0, 3)
{
    boxpos = rd() % 28;
}

bool RandomBox::valid ()
{
    for(Point const& p: getMyBoxes ()) {
        if ( !game.valid (p.line (), p.row ()) ||
             game.exists (p.line (), p.row ()) ) {
            return false;
        }
    }
    return true;
}

bool RandomBox::down ()
{
    for(Point const& p : getNextBoxes(1, 0)) {
        if ( !game.valid (p.line (), p.row ()) ||
             game.exists (p.line (), p.row ()) ) {
            this->set ();
            return false;
        }
    }
    basicPosition.setLine (basicPosition.line () +1);
    return true;
}

bool RandomBox::left ()
{
    for(Point const& p : getNextBoxes(0, -1)) {
        if ( !game.valid (p.line (), p.row ()) ||
             game.exists (p.line (), p.row ()) ) {
            return false;
        }
    }
    basicPosition.setRow (basicPosition.row () -1);
    return true;
}

bool RandomBox::right ()
{
    for(Point const& p : getNextBoxes(0, 1)) {
        if ( !game.valid (p.line (), p.row ()) ||
             game.exists (p.line (), p.row ()) ) {
            return false;
        }
    }
    basicPosition.setRow (basicPosition.row ()+1);
    return true;
}

bool RandomBox::transform ()
{
    for(Point const& p : getNextBoxes()) {
        if ( !game.valid (p.line (), p.row ()) ||
             game.exists (p.line (), p.row ()) ) {
            return false;
        }
    }
    boxpos = dbs[boxpos].next;
    return true;
}

std::vector<Point> RandomBox::getMyBoxes () const
{
    std::vector<Point> mypoints;

    for(Point const& p : dbs[boxpos].boxes ) {
        mypoints.push_back (Point(basicPosition.line () +p.line (),
                                  basicPosition.row () + p.row ()));
    }
    return mypoints;
}

std::vector<Point> RandomBox::getNextBoxes (int line_inc, int row_inc) const
{
    std::vector<Point> nextBoxes;

    for(Point const& p : getMyBoxes () ) {
        nextBoxes.push_back (Point(p.line ()+line_inc, p.row () + row_inc));
    }
    return nextBoxes;
}

std::vector<Point> RandomBox::getNextBoxes () const
{
    std::vector<Point> nextBoxes;

    for(Point const& p : dbs[ dbs[boxpos].next ].boxes ) {
        nextBoxes.push_back (Point(p.line ()+basicPosition.line (),
                                   p.row () + basicPosition.row ()));
    }
    return nextBoxes;
}

void RandomBox::set ()
{
    for(Point const& p : getMyBoxes ()) {
        game.set (p.line (), p.row ());
    }
}

bool RandomBox::inBody (int line, int row) const
{
    for(Point const& p : getMyBoxes () ) {
        if ( p.line () == line && p.row () == row) {
            return true;
        }
    }
    return false;
}

} // namespace restonce
