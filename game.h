#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>

#include "board.h"
#include "score.h"
#include "button.h"


class Game:public QGraphicsView
{
    Q_OBJECT

public:

    void keyPressEvent(QKeyEvent *event);
    void displayMainMenu(QString gameOverText, QString play);
    void gameOver();

    Game(QWidget *parent = 0);
    Score *score;
    QGraphicsScene *gameScene ;
    Board *snake;
    //Board *snake2;
    QLabel *logoLabel;
    QGraphicsTextItem *gameOverText;
    QLabel *helpLabel;
    QGraphicsTextItem *helpText;
    Button *b;

public slots:

    void start();
    void help();
    void back();

};


#endif // GAME_H

