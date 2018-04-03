#include "food.h"

#include <QBrush>


food::food(QGraphicsItem *parent,QString name):QGraphicsPixmapItem(parent)
{
    if(name == "APPLE"){
        setPixmap(QPixmap(":/images/apple.png").scaled(40,40));
        score = 1;
    }
    else{
        setPixmap(QPixmap(":/images/pineapple.png").scaled(40,40,Qt::KeepAspectRatio));
        score = 3;
    }
}
