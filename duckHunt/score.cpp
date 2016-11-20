#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(QString("Hit: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));

}

void Score::increase(){
    score++;
    setPlainText(QString("Hit: ") + QString::number(score));
}

int Score::getScore()
{
    return score;
}


