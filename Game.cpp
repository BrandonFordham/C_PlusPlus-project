#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QImage>
#include "Enemy2.h"
#include <QMediaPlayer>


Game::Game(QWidget * parent){
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // sets scene to 800 by 600
    setBackgroundBrush(QBrush(QImage(":/images/background.png")));


    // make the newly created scene to visualize ( since Game is a
    // QGraphicsView Widget,it can be used to visualize scenes )

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create the player
    player = new Player();
    //player->setRect(0,0,100,100); // rec set to 100 by 100
    player->setPos(350,500); // places in middle of screen

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y()+25);
    scene->addItem(health);

    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(startE2()));
    timer->start(1500);


    //QObject::connect(timer,SIGNAL(timeout()),player,SLOT(startE2()));




    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/backgroundNoise.mp3"));
    music->play();

    show();




}
