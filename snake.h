#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>

class Snake:public QGraphicsPixmapItem
{

public:

    void move();
    void addBehind();
    void checkCollidingObjects();
    void setImage();

    Snake(QGraphicsItem *parent = 0);

    Snake *getForward();
    void setForward(Snake *value);

    Snake *getBackward();
    void setBackward(Snake *value);

    QString getDirection();
    void setDirection(QString value);

    QString part;

private:

    Snake *forward;
    Snake *backward;
    QString direction;

};

#endif // SNAKE_H
