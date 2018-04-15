#include "snake.h"
#include "game.h"
#include "food.h"

#include <QBrush>
#include <QDebug>
#include <typeinfo>

extern Game *game;

SnakePart::SnakePart(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setZValue(1);   //ZValue(1) ustawia węża graficznie nad każdym innym elem. planszy
}

SnakePart *SnakePart::getForward()
{
    return forward;
}

void SnakePart::setForward(SnakePart *value)
{
    forward = value;
}

SnakePart *SnakePart::getBackward()
{
    return backward;
}

void SnakePart::setBackward(SnakePart *value)
{
    backward = value;
}

QString SnakePart::getDirection()
{
    return direction;
}

void SnakePart::setDirection(QString value)
{
    direction = value;
}

void SnakePart::move()
{
    static int first;

    if (direction == "DOWN")
        this->setY(this->y()+40);

    else if(direction == "UP")
        this->setY(this->y()-40);

    else if(direction == "LEFT")
        this->setX(this->x()-40);

    else if(direction == "RIGHT")
        this->setX(this->x()+40);

    if(this->getForward()!= NULL)
        direction = this->getForward()->direction;

    if(first)
    {
        if(this->y() >= 720)
            this->setY(0);

        else if(this->y()<0)
            this->setY(720);

        else if(this->x() < 0)
            this->setX(1000);

        else if(this->x() >= 1000)
            this->setX(0);
    }

    first++;

    if(part == "HEAD")
        checkCollidingObjects();

    setImage();
}

void SnakePart::addBehind()
{
    int x;
    int y;

    if(this->getForward()->getDirection() == "UP")
    {
        x = this->getForward()->x();
        y = this->getForward()->y() + 40;
    }

    else if(this->getForward()->getDirection() == "DOWN")
    {
        x = this->getForward()->x();
        y = this->getForward()->y() - 40;
    }

    else if(this->getForward()->getDirection() == "RIGHT")
    {
        y = this->getForward()->y();
        x = this->getForward()->x() - 40;
    }

    else if(this->getForward()->getDirection() == "LEFT")
    {
        y = this->getForward()->y();
        x = this->getForward()->x() + 40;
    }

    setPos(x,y);
}

void SnakePart::setImage()
{
    if(part == "HEAD")
    {

        if(direction == "UP")
            setPixmap(QPixmap(":/images/images/headup.png").scaled(40,40));

        else if(direction == "DOWN")
            setPixmap(QPixmap(":/images/images/headDown.png").scaled(40,40));

        else if(direction == "LEFT")
            setPixmap(QPixmap(":/images/images/headLeft.png").scaled(40,40));

        else if(direction == "RIGHT")
            setPixmap(QPixmap(":/images/images/head.png").scaled(40,40,Qt::KeepAspectRatio));

        setZValue(2);
    }

    else if(part == "TAIL")
    {
        if(direction == "UP")
          setPixmap(QPixmap(":/images/images/tailUp.png").scaled(40,40));

        else if(direction == "DOWN")
           setPixmap(QPixmap(":/images/images/tailDown.png").scaled(40,40));

        else if(direction == "LEFT")
            setPixmap(QPixmap(":/images/images/tailLeft.png").scaled(40,40));

        else if(direction == "RIGHT")
            setPixmap(QPixmap(":/images/images/tailRight.png").scaled(40,40));
    }

    else if (part == "PART")
        if(direction == this->backward->getDirection())
        {
            if(direction == "LEFT" ||direction ==  "RIGHT")
                setPixmap(QPixmap(":/images/images/left-right.png").scaled(40,40));

            else if (direction == "UP" || direction == "DOWN")
                setPixmap(QPixmap(":/images/images/up-down.png").scaled(40,40));
        }

        else
        {
            if((direction == "UP" && this->backward->getDirection() == "LEFT")
                    || (direction == "RIGHT" && this->backward->getDirection() == "DOWN"))
                setPixmap(QPixmap(":/images/images/leftUp-downRight.png").scaled(40,40));

            else if((direction == "UP" && this->backward->getDirection() == "RIGHT")
                    || (direction == "LEFT" && this->backward->getDirection() == "DOWN"))
                setPixmap(QPixmap(":/images/images/rightUp-downLeft.png").scaled(40,40));

            else if((direction == "LEFT" && this->backward->getDirection() == "UP")
                    || (direction == "DOWN" && this->backward->getDirection() == "RIGHT"))
                setPixmap(QPixmap(":/images/images/upLeft-rightDown.png").scaled(40,40));

            else
                setPixmap(QPixmap(":/images/images/upRight-leftDown.png").scaled(40,40));

        }
}

void SnakePart::checkCollidingObjects()
{
    QList <QGraphicsItem *> coll = this->collidingItems();

    for(int i = 0,n = coll.length(); i < n; i++)
    {
        Food *f = dynamic_cast<Food *>(coll[i]);
        if(f)
        {
            QPointF thisCenter(x(),y());
            QPointF FoodCenter(f->x(),f->y());
            QLineF ln(thisCenter,FoodCenter);
            if(ln.length() == 0)
            {
                game->snake->addPart();
                game->gameScene->removeItem(f);
                game->score->setScore(game->score->getScore()+f->score);
                delete f;
            }
        }

        else if(coll[i])
        {
            if(typeid(*coll[i])== typeid(SnakePart))
            game->gameOver();
            return;
        }
    }
}
