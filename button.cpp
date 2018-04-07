#include "button.h"

#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0,250,80);    //rysowanie kształtu przycisku
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);   //wzór przycisku
    brush.setColor(Qt::darkGreen);  //kolor przycisku
    setBrush(brush);

    text = new QGraphicsTextItem(name,this);    //tworzenie tekstu na przycisku
    int xPos = rect().width()/2- text->boundingRect().width()*2;
    int yPos = rect().height()/2 - text->boundingRect().height()*1.5;
    text->setPos(xPos,yPos);
    QFont newFont("Bold", 36, QFont::Bold, false);
    text->setFont(newFont);
    text->setDefaultTextColor(Qt::white);

    setAcceptHoverEvents(true); //funkcja pozwalająca przyciskowi reagować na przesuwanie nad nim kursorem
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
        emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(event) //zmiana koloru przy najechaniu przycisku myszką
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(event) // zmiana koloru na poprzedni kolor przycisku przy opuszczaniu przycisku myszką
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkGreen);
        setBrush(brush);
    }
}
