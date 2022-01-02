#include "mypushbutton.h"

#include <QPropertyAnimation>
#include <QPainter>

MyPushButton::MyPushButton(QString normalImg,QString pressedImg,QWidget *parent)
    : QPushButton(parent)
    , mNormalImg(normalImg)
    , mPressedImg(pressedImg)
{
    mStat = Normal;
}

void MyPushButton::moveDown()
{
    //     位置大小属性发生变化
    //     给定开始的位置大小属性
    //     给定结束位置大小属性
    //     给定速度，给定动画时长

    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::paintEvent(QPaintEvent *event)
{
    // 绘制按钮图片
    QPainter painter(this);
    QPixmap pix;
    // pix.load(":/res/MenuSceneStartButton.png");
    //    pix.load(mNormalImg);
    if(mStat == Normal)
        pix.load(mNormalImg);
    if(mStat == Pressed)
        pix.load(mPressedImg);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 绘制按钮文字
    painter.drawText(0,0,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    // 鼠标按下切换到Pressed
    this->mStat = Pressed;
    update();
    // 保证信号槽功能
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 鼠标按下切换到Pressed
    this->mStat = Normal;
    update();
    // 保证信号槽功能
    QPushButton::mouseReleaseEvent(e);
}
