#include "selectscene.h"
#include <QPushButton>
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include "playscene.h"

SelectScene::SelectScene(QWidget *parent) : MyMainWindow(parent)
{
    //    QPushButton *btnBack = new QPushButton("Back",this);
    QPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->resize(72,32);
    connect(btnBack,&QPushButton::clicked,this,&SelectScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    // 关卡按钮20个
    const int colWidth = 70;
    const int rowHeight = 70;
    // xy偏移
    const int xOffset = 25;
    const int yOffset = 130;

    for(int i = 0;i<20;++i)
    {
        //        QPushButton *btn = new QPushButton(QString::number(i+1),this);
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        // 排列
        int row = i/4;
        int col = i%4;

        int x = col * colWidth + xOffset;
        int y = row * rowHeight + yOffset;
        btn->resize(57,57);
        btn->move(x,y);
        connect(btn,&MyPushButton::clicked,[=](){
            // 打开新的场景
            PlayScene *playScene = new PlayScene(i+1);
            // 设置playScene关闭的时候自动释放
            playScene->setAttribute(Qt::WA_DeleteOnClose);
            playScene->move(this->pos());
            playScene->show();
            this->hide();

            connect(playScene,&PlayScene::backBtnClicked,[=](){
                this->move(playScene->pos());
                this->show();
                playScene->close();
            });
        });
    }
}

void SelectScene::paintEvent(QPaintEvent *event)
{
    // 绘制背景图片
    QPainter painter(this);

    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix);
}
