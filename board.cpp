#include "board.h"
#include "snakepart.h"

#include <QTimer>
#include <food.h>
#include <QDebug>
#include <QFont>

Board::Board(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    snakeHead = new SnakePart(this);
    snakeHead->setForward(NULL);
    snakeHead->setBackward(NULL);
    snakeHead->setPos(200,200);
    snakeHead->setDirection("RIGHT");
    snakeHead->part = "HEAD";
    snakeHead->setImage();
    snakeTail = snakeHead;

    snakeTimer = new QTimer();
    connect(snakeTimer,SIGNAL(timeout()),this,SLOT(move()));

    appleTimer = new QTimer();
    connect(appleTimer,SIGNAL(timeout()),this,SLOT(makeApple()));

    pineappleTimer = new QTimer();
    connect(pineappleTimer,SIGNAL(timeout()),this,SLOT(makePineapple()));

    direction = "RIGHT";

    //dołączenie trzech części węża do głowy, powstaje początkowy wąż o dł. 4 jedn.
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

//ustawianie kierunku, w którym będzie się poruszał wąż
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

    //ustawianie reakcji planszy na spację
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
   SnakePart *temp = snakeTail;

   while(temp!=NULL)
   {
       temp->move();
       temp = temp->getForward();
   }
}

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

void Board::addPart()
{
    SnakePart *part = new SnakePart(this);
    SnakePart *temp = snakeHead;
    while(temp->getBackward() != NULL)
    {
        temp = temp->getBackward();
    }
    temp->setBackward(part);
    part->setForward(temp);
    part->setBackward(NULL);
    part->addBehind();
    part->setDirection(temp->getDirection());
    snakeTail = part;
    part->part = "TAIL";
    if(temp != snakeHead)
    temp->part = "PART";
    part->setImage();
    temp->setImage();
}

