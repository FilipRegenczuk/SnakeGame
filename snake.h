/* Klasa zajmuje się ustawianiem pozycji węża (kierunek zwrotu elementów) na planszy.
 * Zawarte są tu również interakcje węża i najechanego owocu (czyli wydłużenie
 * węża, usunięcie owocu oraz zwiększenie score'a.
 * */

#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>

//klasa tworząca po kolei każdy kawałek węża
class Snake:public QGraphicsPixmapItem
{

public:

    void move();
    void addBehind();   // ustawia kolejną część węża na koniec
    void checkCollidingObjects();
    void setImage();

    Snake(QGraphicsItem *parent = 0);

    Snake *getForward();    // określa wcześniejszą część węża (przed obecną)
    void setForward(Snake *value);

    Snake *getBackward();   // określa następną część węża
    void setBackward(Snake *value);

    QString getDirection(); //funkcja ustawiająca kierunek, w którym porusza się wąż
    void setDirection(QString value);

    QString part;   // służy do określenia, jaka to część węża (potrzebne do ustawiania obrazka)

private:

    Snake *forward;
    Snake *backward;
    QString direction;

};

#endif // SNAKE_H
