/* Klasa, w której znajduje się wizualizacja owoców
 * oraz ich punktowanie.
 * */

#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsPixmapItem>

class Food:public QGraphicsPixmapItem
{

public:

    Food(QGraphicsItem *parent = 0,QString name = "");
    int score;

};

#endif // FOOD_H
