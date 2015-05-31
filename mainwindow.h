#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <QLabel>
#include "result.h"
#define SIDE 4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int map[SIDE*SIDE];
    void changeLCD(int *map);
    int canmerge(int a,int b);
    bool changed;
    QPixmap& choosepic(int i);
    QPixmap pic;
    void initial();
    void rancreate(bool c);
    void toleft(),toright(),toup(),todown();
    bool checkfinish();
    QLabel *g[SIDE*SIDE];
    Result *r;

protected:
    void keyPressEvent(QKeyEvent *e);
signals:
    result_window(int,bool);
private slots:
    void on_pushButton_clicked();
    void on_checkBox_clicked();
    void on_spinBox_valueChanged();
};

#endif // MAINWINDOW_H
