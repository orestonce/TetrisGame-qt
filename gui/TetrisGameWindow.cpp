#include "TetrisGameWindow.h"
#include "ui_TetrisGameWindow.h"
#include "core/TetrisGame.h"
#include "core/RandomBox.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

TetrisGameWindow::TetrisGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TetrisGameWindow)
{
    ui->setupUi(this);
    m_game = new restonce::TetrisGame;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
             this, SLOT(slot_timeout()));
    this->setFixedSize(this->size());
    m_game->attachObserver(this);
}

void TetrisGameWindow::slot_timeout()
{
    m_game->timeout();
}

TetrisGameWindow::~TetrisGameWindow()
{
    delete ui;
    delete m_game;
}

void TetrisGameWindow::on_pushButton_clicked()
{
    m_timer->start(1000);
    m_game->start();
}

void TetrisGameWindow::paintEvent(QPaintEvent *)
{
    switch(m_game->getGameStatus())
    {
    case restonce::TetrisGame::GameStatus::runing:
        ui->label->setText("正在游戏");
        ui->pushButton->setEnabled(false);
        break;
    case restonce::TetrisGame::GameStatus::stop:
        ui->label->setText("游戏结束");
        ui->pushButton->setEnabled(true);
        break;
    case restonce::TetrisGame::GameStatus::undo:
        ui->label->clear();
        ui->pushButton->setEnabled(true);
        break;
    }
    QPainter painter(this);
    QPoint p2(m_basePosition.x()+ m_boxSize*restonce::TetrisGame::ROW+1,
               m_basePosition.y() -1);
    QPoint p3(m_basePosition.x()-1,
               m_basePosition.y() +m_boxSize*restonce::TetrisGame::LINE+1);
    QPoint p4(m_basePosition.x() + m_boxSize*restonce::TetrisGame::ROW+1,
                m_basePosition.y() + m_boxSize*restonce::TetrisGame::LINE+1);
    QPoint p1(m_basePosition.x()-1, m_basePosition.y()-1);

    painter.drawLine(p1, p2);
    painter.drawLine(p2, p4);
    painter.drawLine(p4, p3);
    painter.drawLine(p1, p3);

    for(int l=0; l<restonce::TetrisGame::LINE; ++l) {
        for(int r=0; r<restonce::TetrisGame::ROW; ++r) {
            QPoint p(m_basePosition.x() + r*m_boxSize,
                     m_basePosition.y() + l*m_boxSize);

            int color = 0;

            if(m_game->exists(l, r))
            {
                color = m_game->color(l, r);
            }
            else if(m_game->getActiveBox() && m_game->getActiveBox()->inBody(l, r))
            {
                color = m_game->getActiveBox()->color();
            }

            if(color <= 0)
                continue;

            QString imgpath = QString::asprintf(":/boxes/images/box%d.jpg", color);

            painter.drawImage(p, QImage(imgpath));

        }
    }
    std::shared_ptr<restonce::RandomBox> nextBox = m_game->getNextBox();
    if(nextBox) {
        QString imgpath = QString::asprintf(":/boxes/images/box%d.jpg", nextBox->color());

        for(restonce::Point const& p : nextBox->getMyBoxes()) {

            painter.drawImage(QPoint(m_baseNextPosition.x() +m_boxSize*p.row(),
                                      m_baseNextPosition.y() + m_boxSize*p.line()),
                               QImage(imgpath));
        }
    }
}

void TetrisGameWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Down:
        m_game->down();
        break;
    case Qt::Key_Left:
        m_game->left();
        break;
    case Qt::Key_Right:
        m_game->right();
        break;
    case Qt::Key_Up:
        m_game->transform();
        break;
    }
}

void TetrisGameWindow::onSubjectChanged()
{
    repaint();
}
