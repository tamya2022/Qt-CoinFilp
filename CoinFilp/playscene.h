#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "coinbutton.h"
#include "mymainwindow.h"

#include <QMainWindow>

class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level,QWidget *parent = nullptr);
    void flip(int row,int col);
    void judegWin();

signals:
    void backBtnClicked();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
private:
    CoinButton *mCoins[4][4];
    bool mHashWin;

};

#endif // PLAYSCENE_H
