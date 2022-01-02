#include "coinbutton.h"
#include "dataconfig.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
    mHashWin = false;
    // 返回按钮
    QPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->resize(72,32);
    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    // 添加左下角的Level
    QLabel *label = new QLabel(this);
    label->setText(QString("Level:%1").arg(level));
    label->resize(150,50);
    // 设置字体
    label->setFont(QFont("华文新魏",20));
    label->move(30,this->height()-label->height());
    // 16个硬币按钮
    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset =57;
    const int yOffset = 200;

    // 取出第几关的二维数组数据
    dataConfig data;
    QVector <QVector <int> > dataArray = data.mData[level];

    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            CoinButton *btn = new CoinButton(this);
            mCoins[row][col] = btn;

            int x = col * colWidth + xOffset;
            int y = row * rowHeight + yOffset;
            // 从屏幕上（0，0）位置开始（即为最左上角的点），显示一个30*35的界面（宽30，高35）。
            // setGeometry (0, 0, 30, 35)
            btn->setGeometry(x,y,50,50);
            btn->setStat(dataArray[row][col]);

            connect(btn,&CoinButton::clicked,[=](){
                // 每次点击时翻转
                //                btn->flip();
                this->flip(row,col);
            });
        }
    }
}

void PlayScene::flip(int row,int col)
{
    if(mHashWin)
    {
        return;
    }
    this->mCoins[row][col]->flip();
    QSound::play(":/res/ConFlipSound.wav");
    QTimer::singleShot(250,[=](){
        // 翻动上下左右的硬币
        if(row+1<4)
        {
            this->mCoins[row+1][col]->flip();
        }
        if(row-1>=0)
        {
            this->mCoins[row-1][col]->flip();
        }
        if(col-1>=0)
        {
            this->mCoins[row][col-1]->flip();
        }
        if(col+1<4)
        {
            this->mCoins[row][col+1]->flip();
        }
        // 判断游戏是否胜利
        this->judegWin();
    });
}

void PlayScene::judegWin()
{
    qDebug()<<"Judge Win";
    // 16个硬币按钮判断状态都是1
    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            //
            if(!this->mCoins[row][col]->getStat())
            {
                // 不是全部金币，就返回
                qDebug()<<"return ";
                return;
            }
        }
    }
    mHashWin = true;
    QSound::play(":/res/LevelWinSound.wav");
    // 游戏结束
    //    QMessageBox::information(this,"恭喜","你胜利了");
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();

    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin
                                                           ,"geometry"
                                                           ,this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x()
                                 ,labelWin->y()+100
                                 ,labelWin->width()
                                 ,labelWin->height()));
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    // 绘制背景图片
    QPainter painter(this);

    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    // 将logo缩放到50%
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);
}
