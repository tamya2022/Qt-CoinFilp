#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);
    int getStat() const;
    void setStat(int stat);
    void flip();
    //  翻转动画
    void setStatWithAnimation(int stat);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    // 硬币状态，0表示银币
    int mStat;
    int mFrame;
    QTimer mTimer;
};

#endif // COINBUTTON_H
