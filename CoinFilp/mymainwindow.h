#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

private slots:
    void on_actionQuit_triggered();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::MyMainWindow *ui;
};

#endif // MYMAINWINDOW_H
