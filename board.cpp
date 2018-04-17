#include "board.h"
#include "snake.h"

#include <QTimer>
#include <food.h>
#include <QDebug>
#include <QFont>

Board::Board(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // stworzenie i umiejscownienie na planszy węża
    snakeHead = new Snake(this);
    snakeHead->setForward(NULL);    // ustawienie głowy jako pierwszego kawałka
    snakeHead->setBackward(NULL);
    snakeHead->setPos(200,200);
    snakeHead->setDirection("RIGHT");
    snakeHead->part = "HEAD";
    snakeHead->setImage();
    snakeTail = snakeHead;

    // timery do węża i owoców
    snakeTimer = new QTimer();
    connect(snakeTimer,SIGNAL(timeout()),this,SLOT(move()));

    appleTimer = new QTimer();
    connect(appleTimer,SIGNAL(timeout()),this,SLOT(makeApple()));

    pineappleTimer = new QTimer();
    connect(pineappleTimer,SIGNAL(timeout()),this,SLOT(makePineapple()));

    direction = "RIGHT";

    // dołączenie trzech części węża do głowy, powstaje początkowy wąż o dł. 4 jedn.
    addPart();
    addPart();
    addPart();

    text = new QGraphicsTextItem(this);
    text->setVisible(true);
    text->setPlainText("press Space to continue");
    text->setPos(300, 300);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("bold",25, QFont::Bold, false));

}

// klasa zajmująca się sterowaniem za pomocą klawiszy WASD oraz reakcją na space
void Board::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_S && snakeHead->getDirection() != "UP")
    {
        direction = "DOWN";
    }

    else if(event->key() == Qt::Key_W && snakeHead->getDirection() != "DOWN")
    {
        direction = "UP";
    }

    else if(event->key() == Qt::Key_D && snakeHead->getDirection() != "LEFT")
    {
        direction = "RIGHT";
    }

    else if(event->key() == Qt::Key_A && snakeHead->getDirection() != "RIGHT")
    {
        direction = "LEFT";
    }

    // ustawianie reakcji planszy na spację
    else if(event->key() == Qt::Key_Space)
    {
        if(snakeTimer->isActive())
        {
            appleTimer->stop();
            pineappleTimer->stop();
            snakeTimer->stop();
            text->setVisible(true);
        }

        else
        {
            appleTimer->start(5000);
            pineappleTimer->start(15000);
            snakeTimer->start(100);
            text->setVisible(false);
        }
    }
}

void Board::move()
{
    snakeHead->setDirection(direction);
    moveSnake();
}

void Board::moveSnake()
{
   Snake *temp = snakeTail;

   while(temp!=NULL)
   {
       temp->move();    //move() z klasy Snake
       temp = temp->getForward();
   }
}

// klasy tworzące owoce i umieszczające je w losowych miejscach na planszy
void Board::makeApple()
{
    Food * f1 = new Food(this,"APPLE");
    f1->setX(qrand() % (1000/40)* 40);
    f1->setY(qrand() % (720/40) * 40);
}
void Board::makePineapple()
{
    Food * f1 = new Food(this);
    f1->setX(qrand() % (1000/40)* 40);
    f1->setY(qrand() % (720/40) * 40);
}

// klasa zajmująca się wydłużaniem węża po zjedzeniu obiektu
void Board::addPart()
{
    Snake *part = new Snake(this);
    Snake *temp = snakeHead;
    while(temp->getBackward() != NULL)  //ustawienie 'tempt' jako ostatni kawałek węża
    {
        temp = temp->getBackward();
    }
    temp->setBackward(part);    // ustawiamy part jako część kolejną po tempt
    part->setForward(temp);     // ustawiamy tempt jako część przed part
    part->setBackward(NULL);
    part->addBehind();
    part->setDirection(temp->getDirection());   // ustawiamy kierunek part taki jak ma tempt
    snakeTail = part;   // ustawiamy part jako snakeTail
    part->part = "TAIL";
    if(temp != snakeHead)   // jeśli wcześniejszy kawałek nie jest głową
    temp->part = "PART";    // definiujemy go jako "PART"
    part->setImage();
    temp->setImage();
}

