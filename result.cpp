#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
}

Result::~Result()
{
    delete ui;
}

void Result::initial(int score,bool win){
    ui->score->setNum(score);
    if(win){
        ui->inform->setText("You Win!!");
    }else{
        ui->inform->setText("Game Over!!");
    }
}

void Result::on_Restart_clicked()
{
    this->close();
}
