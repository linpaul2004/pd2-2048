#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map[7]=2;
    map[15]=2;
    std::srand(std::time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeLCD(int *map){
    ui->g00->display(map[0]);
    ui->g01->display(map[1]);
    ui->g02->display(map[2]);
    ui->g03->display(map[3]);
    ui->g10->display(map[4]);
    ui->g11->display(map[5]);
    ui->g12->display(map[6]);
    ui->g13->display(map[7]);
    ui->g20->display(map[8]);
    ui->g21->display(map[9]);
    ui->g22->display(map[10]);
    ui->g23->display(map[11]);
    ui->g30->display(map[12]);
    ui->g31->display(map[13]);
    ui->g32->display(map[14]);
    ui->g33->display(map[15]);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Up:
        for(int row=1;row<SIDE;row++){
            for(int col=0;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[(row-1)*SIDE+col]);
                if(v!=0){
                    map[(row-1)*SIDE+col]=v;
                    map[row*SIDE+col]=0;
                }
            }
        }
        for(int row=1;row<SIDE;row++){
            for(int col=0;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=row;i>0;i--){
                        if(map[(i-1)*SIDE+col]==0){
                            map[(i-1)*SIDE+col]=map[i*SIDE+col];
                            map[i*SIDE+col]=0;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        for(int col=0;col<4;col++){
            if(map[(SIDE-1)*SIDE+col]==0){
                if(std::rand()%2){
                    map[(SIDE-1)*SIDE+col]=2;
                }
            }
        }
        changeLCD(map);
        break;
    }
}

int MainWindow::canmerge(int a,int b){
    if(a==b){
        return a+b;
    }else{
        return 0;
    }
}
