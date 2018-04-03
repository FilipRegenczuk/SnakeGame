#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>

#include "movesnake.h"
#include "score.h"
#include "button.h"


class Game:public QGraphicsView
{

    Q_OBJECT

public:

    Game(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    Score *score;
    QGraphicsScene *gameScene ;
    MoveSnake *snake;
    MoveSnake *snake2;
    void displayMainMenu(QString title, QString play);
    QLabel *logoLabel;
    QGraphicsTextItem *titleText;
    Button *b;
    void gameOver();

public slots:

    void start();
    void help();

};


#endif // GAME_H

