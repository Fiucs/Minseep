#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"game_module.h"
#include<QMouseEvent>
#include<QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void analysis(int x,int y,std::vector<std::vector<Mineinfo>> gameinfo,int row,int cow);
    void searchall0(int x,int y,int row,int cow);//空块为0时爆开
    void succes();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    game_module create;//实例化模型类

private:
    Ui::MainWindow *ui;
    int arryx;//记录鼠标位置转换的下标x
    int arryy;//记录鼠标位置转换数字的下标y
    int flag=0;//初始状态 不是右键
    int number;//初始执行状态
    QLabel *win;
protected:
    virtual void paintEvent(QPaintEvent *event);//绘制事件
     void mousePressEvent(QMouseEvent *e);//鼠标点击事件 左键，右键
signals:
     void clicpos();

private slots:
     void shows();




     void on_actionstart_triggered();
};

#endif // MAINWINDOW_H
