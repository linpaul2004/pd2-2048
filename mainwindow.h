#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <cstdlib>
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

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H