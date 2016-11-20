#ifndef ENEMY2_CPP
#define ENEMY2_CPP

#include "Enemy2.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"

extern Game * game;

Enemy2::Enemy2(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    int random_number = rand() % 700;
    setPixmap(QPixmap(":/images/enemy2.png"));
    setPos(random_number, 0);

    //setPixmap(QPixmap(":/images/enemy2.png"));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(40);
}

void Enemy2::move(){
    setPos(x(),y()+5);

    if(pos().y() > 600){
        game->health->decrease();
        scene()->removeItem(this);
        delete this;
    }
}

#endif // ENEMY2_CPP
