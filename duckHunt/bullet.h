#ifndef BULLET_H
#define BULLET_H

//originally used QGraphicsRectItem and changed to pix for pictures

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);
public slots:
    void move();
private:
    QMediaPlayer * duckSound;
};

#endif // BULLET_H
