#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::srand(std::time(NULL));
    initial();
    changeLCD(map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial(){
    int r1=std::rand()%SIDE*SIDE,r2=0;
    for(int i=0;i<SIDE*SIDE;i++){
        map[i]=0;
    }
    while(r1==r2){
        r2=std::rand()%SIDE*SIDE;
    }
    map[r1]=2;
    map[r2]=2;
}

void MainWindow::changeLCD(int *map){
    ui->g00->setPixmap(choosepic(map[0]));
    ui->g01->setPixmap(choosepic(map[1]));
    ui->g02->setPixmap(choosepic(map[2]));
    ui->g03->setPixmap(choosepic(map[3]));
    ui->g10->setPixmap(choosepic(map[4]));
    ui->g11->setPixmap(choosepic(map[5]));
    ui->g12->setPixmap(choosepic(map[6]));
    ui->g13->setPixmap(choosepic(map[7]));
    ui->g20->setPixmap(choosepic(map[8]));
    ui->g21->setPixmap(choosepic(map[9]));
    ui->g22->setPixmap(choosepic(map[10]));
    ui->g23->setPixmap(choosepic(map[11]));
    ui->g30->setPixmap(choosepic(map[12]));
    ui->g31->setPixmap(choosepic(map[13]));
    ui->g32->setPixmap(choosepic(map[14]));
    ui->g33->setPixmap(choosepic(map[15]));
}

QPixmap& MainWindow::choosepic(int i){
    switch(i){
    case 0:
        pic.load(":/res/0.png");
        break;
    case 2:
        pic.load(":/res/2.png");
        break;
    case 4:
        pic.load(":/res/4.png");
        break;
    case 8:
        pic.load(":/res/8.png");
        break;
    case 16:
        pic.load(":/res/16.png");
        break;
    case 32:
        pic.load(":/res/32.png");
        break;
    case 64:
        pic.load(":/res/64.png");
        break;
    case 128:
        pic.load(":/res/128.png");
        break;
    }
    return pic;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Up:
        changed=false;
        for(int row=1;row<SIDE;row++){
            for(int col=0;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=row;i>0;i--){
                        if(map[(i-1)*SIDE+col]==0){
                            map[(i-1)*SIDE+col]=map[i*SIDE+col];
                            map[i*SIDE+col]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
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
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        if(changed==true){
            for(int i=0;i<SIDE*SIDE;i++){
                if(map[i]==0){
                    if(std::rand()%2){
                        map[i]=2;
                        break;
                    }
                }
            }
        }
        changeLCD(map);
        break;
    case Qt::Key_Down:
        changed=false;
        for(int row=SIDE-2;row>=0;row--){
            for(int col=0;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=row;i<SIDE-1;i++){
                        if(map[(i+1)*SIDE+col]==0){
                            map[(i+1)*SIDE+col]=map[i*SIDE+col];
                            map[i*SIDE+col]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        for(int row=SIDE-2;row>=0;row--){
            for(int col=0;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[(row+1)*SIDE+col]);
                if(v!=0){
                    map[(row+1)*SIDE+col]=v;
                    map[row*SIDE+col]=0;
                }
            }
        }
        for(int row=SIDE-2;row>=0;row--){
            for(int col=0;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=row;i<SIDE-1;i++){
                        if(map[(i+1)*SIDE+col]==0){
                            map[(i+1)*SIDE+col]=map[i*SIDE+col];
                            map[i*SIDE+col]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        if(changed==true){
            for(int i=0;i<SIDE*SIDE;i++){
                if(map[i]==0){
                    if(std::rand()%2){
                        map[i]=2;
                        break;
                    }
                }
            }
        }
        changeLCD(map);
        break;
    case Qt::Key_Left:
        changed=false;
        for(int row=0;row<SIDE;row++){
            for(int col=1;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=col;i>0;i--){
                        if(map[row*SIDE+i-1]==0){
                            map[row*SIDE+i-1]=map[row*SIDE+i];
                            map[row*SIDE+i]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        for(int row=0;row<SIDE;row++){
            for(int col=1;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[row*SIDE+col-1]);
                if(v!=0){
                    map[row*SIDE+col-1]=v;
                    map[row*SIDE+col]=0;
                }
            }
        }
        for(int row=0;row<SIDE;row++){
            for(int col=1;col<SIDE;col++){
                if(map[row*SIDE+col]!=0){
                    for(int i=col;i>0;i--){
                        if(map[row*SIDE+i-1]==0){
                            map[row*SIDE+i-1]=map[row*SIDE+i];
                            map[row*SIDE+i]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        if(changed==true){
            for(int i=0;i<SIDE*SIDE;i++){
                if(map[i]==0){
                    if(std::rand()%2){
                        map[i]=2;
                        break;
                    }
                }
            }
        }
        changeLCD(map);
        break;
    case Qt::Key_Right:
        changed=false;
        for(int row=0;row<SIDE;row++){
            for(int col=SIDE-2;col>=0;col--){
                if(map[row*SIDE+col]!=0){
                    for(int i=col;i<SIDE-1;i++){
                        if(map[row*SIDE+i+1]==0){
                            map[row*SIDE+i+1]=map[row*SIDE+i];
                            map[row*SIDE+i]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        for(int row=0;row<SIDE;row++){
            for(int col=SIDE-2;col>=0;col--){
                int v=canmerge(map[row*SIDE+col],map[row*SIDE+col+1]);
                if(v!=0){
                    map[row*SIDE+col+1]=v;
                    map[row*SIDE+col]=0;
                }
            }
        }
        for(int row=0;row<SIDE;row++){
            for(int col=SIDE-2;col>=0;col--){
                if(map[row*SIDE+col]!=0){
                    for(int i=col;i<SIDE-1;i++){
                        if(map[row*SIDE+i+1]==0){
                            map[row*SIDE+i+1]=map[row*SIDE+i];
                            map[row*SIDE+i]=0;
                            changed=true;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        if(changed==true){
            for(int i=0;i<SIDE*SIDE;i++){
                if(map[i]==0){
                    if(std::rand()%2){
                        map[i]=2;
                        break;
                    }
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
