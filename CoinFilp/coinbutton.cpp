#include "coinbutton.h"
#include <QPainter>
#include <QDebug>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    // 初始状态设置
    this->setStat(0);
    // 样式设置
    this->setStyleSheet("QPushButton{border:0px;}");

    // 动画定时器信号和槽
    connect(&this->mTimer,&QTimer::timeout,[=](){
        if(this->mStat)
        {
            this->mFrame--;
        }
        else {
            this->mFrame++;
        }
        // 加载相应帧的图片
        QString frameName = QString(":/res/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frameName));
        // 停止计时器
        if(this->mFrame ==8 || this->mFrame ==1)
        {
            this->mTimer.stop();
        }
    });
}

int CoinButton::getStat() const
{
    return mStat;
}

void CoinButton::setStat(int stat)
{
    mStat = stat;
    if(this->mStat)
    {
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else {
        // 银币图标
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    this->setIconSize(this->size());
}

void CoinButton::flip()
{
    //  this->setStat(!this->getStat());
    this->setStatWithAnimation(!this->getStat());
}

void CoinButton::setStatWithAnimation(int stat)
{
    this->mStat = stat;
    if(this->mStat)
    {
        this->mFrame = 8;
    }
    else {
        this->mFrame = 1;
    }
    this->mTimer.start(30);
}

void CoinButton::paintEvent(QPaintEvent *event)
{
    // 绘制按钮图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    QPushButton::paintEvent(event);
}


void CoinButton::mouseDoubleClickEvent(QMouseEvent *event) {} //禁止使用 鼠标双击
