#include "food.h"

#include <QBrush>

Food::Food(QGraphicsItem *parent,QString name):QGraphicsPixmapItem(parent)
{
    if(name == "APPLE")
    {
        setPixmap(QPixmap(":/images/images/apple.png").scaled(40,40));
        score = 1;
    }

    else
    {
        setPixmap(QPixmap(":/images/images/pineapple.png").scaled(40,40,Qt::KeepAspectRatio));
        score = 3;
    }
}
