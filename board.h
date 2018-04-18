#ifndef BOARD_H
#define BOARD_H
#include <QKeyEvent>
#include <QGraphicsItem>

#include "snake.h"

class Board:public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:

    Board(QGraphicsItem *parent = 0);

    void keyPressEvent(QKeyEvent *event);
    void addPart();     // funkcja dodająca każdy kolejny kawałek węża
    void moveSnake();

public slots:

    void move();    // funkcja poruszająca każym kawałkiem węża przy pomocy moveSnake
    void makeApple();
    void makePineapple();

private:

    Snake               *snakeHead;
    Snake               *snakeTail;
    QString              direction;
    QTimer              *snakeTimer;        //szybkość, z jaką porusza się wąż
    QTimer              *appleTimer;        //czas, po którym pojawia się nowe jabłko
    QTimer              *pineappleTimer;    //czas, po którym pojawia się nowy ananas
    QGraphicsTextItem   *text;
};

#endif // MOVESNAKE_H

