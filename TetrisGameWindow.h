#ifndef TETRISGAMEWINDOW_H
#define TETRISGAMEWINDOW_H

#include <QWidget>
#include <QPoint>

namespace Ui {
class TetrisGameWindow;
}
class QTimer;

namespace restonce {
class TetrisGame;
}

class TetrisGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TetrisGameWindow(QWidget *parent = 0);
    ~TetrisGameWindow();
protected:
    void paintEvent (QPaintEvent *);
    void keyPressEvent (QKeyEvent *);
private slots:
    void on_pushButton_clicked();
    void slot_timeout();
private:
    Ui::TetrisGameWindow *ui;
    restonce::TetrisGame *game;
    int boxSize = 24;
    QPoint basePosition = QPoint(10, 10);
    QPoint baseNextPosition = QPoint(200, 240);
    QTimer *timer;
};

#endif // TETRISGAMEWINDOW_H
