#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "Bullet.h"
#include <QDebug>
#include "Enemy.h"
#include "Enemy2.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Player.png"));
    setTransformOriginPoint(60,60);
    setRotation(270);

    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/bulletSound.mp3"));
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if(pos().x() > 0)
            setPos(x()-20,y());
    }
    else if(event->key() == Qt::Key_Right){
        if(pos().x() + 100 < 800)
            setPos(x()+20,y());
    }
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+40,y());
        scene()->addItem(bullet);


         //play bulletsound
        if(bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);

        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }


    }
}

void Player::spawn()
{
    //create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);

}

void Player::startE2()
{
    Enemy2 * enemy2 = new Enemy2();
    scene()->addItem(enemy2);
}
