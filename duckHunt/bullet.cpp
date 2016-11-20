#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"
#include <typeinfo>
#include "Enemy2.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
     setPixmap(QPixmap(":/images/bulletGraphic.png"));

     //bulletsound->setMedia(QUrl("qrc:/sounds/bulletSound.mp3"));

     duckSound = new QMediaPlayer();
     duckSound->setMedia(QUrl("qrc:/sounds/duckSound.mp3"));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(25);
}

void Bullet::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Enemy) ||
           typeid(*(colliding_items[i])) == typeid(Enemy2)){
            game->score->increase();

            // duck death sound
            duckSound->play();

            // removes bullets/memory management
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;

            return;

        }
    }

    setPos(x(),y()-10);
    if(pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }

}
