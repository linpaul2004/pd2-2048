#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = 0);
    ~Result();

private:
    Ui::Result *ui;
public slots:
    void initial(int score,bool win);
private slots:
    void on_Restart_clicked();
};

#endif // RESULT_H
