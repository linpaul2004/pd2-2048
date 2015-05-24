#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <cstdlib>
#include <cstdio>
#include <ctime>
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
    int map[16];
    void changeLCD(int *map);
    int canmerge(int a,int b);
    bool changed;
    QPixmap& choosepic(int i);
    QPixmap pic;
    void initial();
    void rancreate(bool c);

protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
