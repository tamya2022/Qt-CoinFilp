#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum MyPushButtonStat{
        Normal,
        Pressed
    };
    explicit MyPushButton(QString normalImg,QString pressedImg,QWidget *parent = nullptr);
    //往下和往上的动画函数
    void moveDown();
    void moveUp();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:

private:
    // 正常状态的图片和鼠标按下的图片
    QString mNormalImg;
    QString mPressedImg;
    // 按钮状态
    MyPushButtonStat mStat;
};



#endif // MYPUSHBUTTON_H
