#include "movesnake.h"
#include "snakepart.h"
#include <QTimer>
#include <food.h>
#include <QDebug>
#include <QFont>
MoveSnake::MoveSnake(QGraphicsItem *parent):QGraphicsRectItem(parent)
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

    foodTimer = new QTimer();
    connect(foodTimer,SIGNAL(timeout()),this,SLOT(makeFood()));

    food2Timer = new QTimer();
    connect(food2Timer,SIGNAL(timeout()),this,SLOT(makeFood2()));

    direction = "RIGHT";

    addPart();
    addPart();
    addPart();

    text = new QGraphicsTextItem(this);
    text->setVisible(true);
    text->setPlainText("press Space to continue");
    text->setPos(300, 300);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("bold",25, QFont::Bold, false));


//  /  makeBoard();

}

void MoveSnake::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_S && snakeHead->getDirection() != "UP") {
      //  snake->setY(snake->y()+40);
        direction = "DOWN";
    }
    else if(event->key() == Qt::Key_W && snakeHead->getDirection() != "DOWN") {
      //  snake->setY(snake->y()-40);
        direction = "UP";
    }
    else if(event->key() == Qt::Key_D && snakeHead->getDirection() != "LEFT") {
      //  snake->setX(snake->x()+40);
        direction = "RIGHT";
    }
    else if(event->key() == Qt::Key_A && snakeHead->getDirection() != "RIGHT") {
        //snake->setX(snake->x()-40);
        direction = "LEFT";
    }
    else if(event->key() == Qt::Key_Space){
        if(snakeTimer->isActive()){
            foodTimer->stop();
            food2Timer->stop();
        snakeTimer->stop();
        text->setVisible(true);
        }
        else{

            foodTimer->start(5000);
            food2Timer->start(15000);
            snakeTimer->start(100);
            text->setVisible(false);
        }

    }
}

void MoveSnake::makeBoard()
{
    for(int i = 0 ;i <9*5;i++){
        for(int j = 0; j < 14*5; j++) {
            QGraphicsRectItem *rect= new QGraphicsRectItem(this);
            rect->setRect(j*40,i*40,40,40);
        }
    }



}

void MoveSnake::move() {
    snakeHead->setDirection(direction);
    moveSnake();

}

void MoveSnake::makeFood()
{
    Food * f1 = new Food(this,"APPLE");
    f1->setX(qrand() % (1000/40)* 40);
    f1->setY(qrand() % (720/40) * 40) ;

}
void MoveSnake::makeFood2()
{
    Food * f1 = new Food(this);
    f1->setX(qrand() % (1000/40)* 40);
    f1->setY(qrand() % (720/40) * 40) ;

}

void MoveSnake::addPart(){
    SnakePart *part = new SnakePart(this);
    SnakePart *temp = snakeHead;
    while(temp->getBackward() != NULL) {
        temp = temp->getBackward();
    }
    temp->setBackward( part);
    part->setForward( temp);
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

void MoveSnake::moveSnake()
{
    //qDebug() << "Entry";
   SnakePart *temp = snakeTail;

   while(temp!=NULL) {
    //   qDebug() << "Enry 2";
       temp->move();
       temp = temp->getForward();
   }
}

