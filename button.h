#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QFont>

class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT

public:

    Button(QString name, QGraphicsItem * parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:

    QGraphicsTextItem *text;

signals:

    void clicked();

};
#endif // BUTTON_H
