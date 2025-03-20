#include "mywidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    mp.load(":/pic/111.png");
}

void MyWidget::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.drawPixmap(0, 0, width(), height(),mp);
}

