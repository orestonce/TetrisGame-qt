#include "TetrisGameWindow.h"
#include "ui_TetrisGameWindow.h"
#include "TetrisGame.h"
#include "RandomBox.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

TetrisGameWindow::TetrisGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TetrisGameWindow)
{
    ui->setupUi(this);
    game = new restonce::TetrisGame;
    timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()),
             this, SLOT(slot_timeout()) );
    this->setFixedSize (this->size ());
}

void TetrisGameWindow::slot_timeout ()
{
    game->timeout ();
    repaint ();
}

TetrisGameWindow::~TetrisGameWindow()
{
    delete ui;
}

void TetrisGameWindow::on_pushButton_clicked()
{
    timer->start (1000);
    game->start ();
    repaint ();
}

void TetrisGameWindow::paintEvent (QPaintEvent *)
{
    switch ( game->getGameStatus () )
    {
    case restonce::TetrisGame::GameStatus::runing:
        ui->label->setText (trUtf8 ("正在游戏"));
        ui->pushButton->setEnabled (false);
        break;
    case restonce::TetrisGame::GameStatus::stop:
        ui->label->setText (trUtf8 ("游戏结束"));
        ui->pushButton->setEnabled (true);
        break;
    case restonce::TetrisGame::GameStatus::undo:
        ui->label->clear ();
        ui->pushButton->setEnabled (true);
        break;
    }
    QPainter painter(this);
    QPoint p2( basePosition.x ()+ boxSize*restonce::TetrisGame::ROW,
               basePosition.y () );
    QPoint p3( basePosition.x (),
               basePosition.y () +boxSize*restonce::TetrisGame::LINE);
    QPoint p4 ( basePosition.x () + boxSize*restonce::TetrisGame::ROW,
                basePosition.y () + boxSize*restonce::TetrisGame::LINE);
    QPoint p1(basePosition);

    painter.drawLine (p1, p2);
    painter.drawLine (p2, p4);
    painter.drawLine (p4, p3);
    painter.drawLine (p1, p3);

    for(int l=0; l<restonce::TetrisGame::LINE; ++l) {
        for(int r=0; r<restonce::TetrisGame::ROW; ++r) {
            QPoint p(basePosition.x () + r*boxSize,
                     basePosition.y () + l*boxSize);
            if ( game->exists (l, r)
                 || game->inActiveBox (l,r)) {
                painter.drawImage ( p, QImage(":/boxes/box.png"));
            }
        }
    }
    std::shared_ptr<restonce::RandomBox> nextBox = game->getNextBox ();
    if ( nextBox ) {
        for(restonce::Point const& p : nextBox->getMyBoxes () ) {
            painter.drawImage (QPoint(baseNextPosition.x () +boxSize*p.row (),
                                      baseNextPosition.y () + boxSize*p.line ()),
                               QImage(":/boxes/box.png"));
        }
    }
}

void TetrisGameWindow::keyPressEvent (QKeyEvent *e)
{
    switch (e->key ())
    {
    case Qt::Key_Down:
        game->down ();
        break;
    case Qt::Key_Left:
        game->left ();
        break;
    case Qt::Key_Right:
        game->right ();
        break;
    case Qt::Key_Up:
        game->transform ();
        break;
    }
    repaint ();
}
