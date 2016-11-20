#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h> // rand() -> really large int
#include <QKeyEvent>
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(){
    // set random position
    int random_number_x = rand() % 700;


    setPos(random_number_x,0);

    // drew the rect
    setPixmap(QPixmap(":/images/enemyGraphic.png"));

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // 10
    timer->start(5);
}

void Enemy::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::LeftButton){
        scene()->removeItem(this);
        delete this;
    }

}



void Enemy::move(){
    //int random_number2 = 300 + (rand() % 300);
    // move enemy down
    int direction = rand() % 2;
    int changeX = 1;//rand() % 20;
    int changeY = 5;rand() % 5;

    if(pos().y() < 50){
        if(direction == 0){
            setPos(x()+changeX, y()+1);
        }
    }
    else if(pos().y() < 200){
        if(direction == 0){
            setPos(x()-changeX,y()+1);
        }

    }
    else if(pos().y() < 400){
        if(direction == 0){
            setPos(x()+changeX,y()+1);
        }
    }
    else if(pos().y() < 600){
        if(direction == 0){
            setPos(x()-changeX,y()+1);
        }
    }
    else{
        setPos(x(),y()+1);
    }




    //keeps duck on screen
    if (pos().x() > 700)
    {
        setPos(x()-2,y());
    }
    else if(pos().x()  < 0){
        setPos(x()+2,y());
    }

    if (pos().y() < 0) {
        scene()->removeItem(this);
        delete this;
    }

    if(pos().y() > 600){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }

}


