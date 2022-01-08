#include "startscene.h"
#include "mypushbutton.h"
#include <QPushButton>
#include <QTimer>
#include <QSound>

StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("开始场景");

    // QPushButton *btnStart = new QPushButton(this);
    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png"
                                              ,":/res/MenuSceneStartButton.png"
                                              ,this);
    btnStart->resize(114,114);
    // 按钮水平居中，垂直方向在3/4位置
    btnStart->move((this->width()-btnStart->width())/2,
                   this->height()*3/4-btnStart->height()/2);
    // This指针指向被调用的成员函数所属的对象。
    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=](){
        QSound::play(":/res/BackButtonSound.wav");
        this->show();
        this->mSelectScene.hide();
        this->mSelectScene.move(this->pos());

    });

    connect(btnStart,&MyPushButton::clicked,[=]{
        QSound::play(":/res/TapButtonSound.wav");
        // 将按钮设置为不可用
        btnStart->setEnabled(false);
        // 播放向下的动画
        btnStart->moveDown();
        QTimer::singleShot(150,[=](){
            // 等待往下动画放完，再调用往上走的动画
            btnStart->moveUp();
        });

        QTimer::singleShot(300,[=](){
            // 将按钮设置为可用
            btnStart->setEnabled(true);
            // 隐藏当前窗口
            this->hide();
            // 显示第二个窗口
            this->mSelectScene.show();
            this->mSelectScene.move(this->pos());
        });

    });
}
