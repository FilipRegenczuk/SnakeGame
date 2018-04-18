/* Klasa służąca do przedstawiania wyniku gry.
 * */

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score:public QGraphicsTextItem
{

public:

    Score(QGraphicsItem *parent = 0);

    int getScore() ;
    void getScore(int value);

private:

    int score;

};

#endif // SCORE_H
