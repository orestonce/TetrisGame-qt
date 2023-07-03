#ifndef TETRISGAMEWINDOW_H
#define TETRISGAMEWINDOW_H

#include <QWidget>
#include <QPoint>
#include "core/Subject.h"

namespace Ui {
class TetrisGameWindow;
}
class QTimer;

namespace restonce {
class TetrisGame;
}

class TetrisGameWindow
        : public QWidget, public restonce::Observer
{
    Q_OBJECT

public:
    explicit TetrisGameWindow(QWidget *parent = 0);
    ~TetrisGameWindow();
protected:
    void paintEvent(QPaintEvent *) override final;
    void keyPressEvent(QKeyEvent *) override final;
    virtual void onSubjectChanged() override final;
private slots:
    void on_pushButton_clicked();
    void slot_timeout();
private:
    Ui::TetrisGameWindow *ui;
    restonce::TetrisGame *m_game;
    int m_boxSize = 24;
    QPoint m_basePosition = QPoint(10, 10);
    QPoint m_baseNextPosition = QPoint(200, 240);
    QTimer *m_timer;
};

#endif // TETRISGAMEWINDOW_H
