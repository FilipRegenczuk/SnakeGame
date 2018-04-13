#ifndef BOARD_H
#define BOARD_H
#include <QKeyEvent>
#include <QGraphicsItem>

#include "snakepart.h"

class Board:public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:

    Board(QGraphicsItem *parent = 0);

    void keyPressEvent(QKeyEvent *event);
    void addPart();
    void moveSnake();

public slots:

    void move();
    void makeApple();
    void makePineapple();

private:

    SnakePart *snakeHead;
    SnakePart *snakeTail;
    QString direction;
    QTimer *snakeTimer; //szybkość, z jaką porusza się wąż
    QTimer *appleTimer;  //czas, po którym pojawia się nowe jabłko
    QTimer *pineappleTimer; //czas, po którym pojawia się nowy ananas
    QGraphicsTextItem *text;
};

#endif // MOVESNAKE_H

