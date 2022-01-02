#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include "mymainwindow.h"

#include <QMainWindow>

class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void backBtnClicked();

public slots:
};

#endif // SELECTSCENE_H
