#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::srand(std::time(NULL));
    for(int i=0;i<SIDE*SIDE;i++){
        g[i]=new QLabel(this);
        g[i]->setGeometry(20+(i%4)*100,120+(i/4)*100,100,100);
        g[i]->setScaledContents(true);
    }
    initial();
    changeLCD(map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial(){
    int r1=0,r2=0;
    for(int i=0;i<SIDE*SIDE;i++){
        map[i]=0;
    }
    while(r1==r2){
        r1=std::rand()%(SIDE*SIDE);
        r2=std::rand()%(SIDE*SIDE);
    }
    map[r1]=2;
    map[r2]=2;
}

void MainWindow::changeLCD(int *map){
    for(int i=0;i<SIDE*SIDE;i++){
        g[i]->setPixmap(choosepic(map[i]));
    }
    int score=0;
    for(int i=0;i<SIDE*SIDE;i++){
        score+=map[i]*map[i];
    }
    ui->score->setNum(score);
}

QPixmap& MainWindow::choosepic(int i){
    char c[25];
    std::sprintf(c,":/res/%d.png",i);
    pic.load(c);
    return pic;
}

void MainWindow::rancreate(bool c){
    if(c==true){
        while(1){
            for(int i=SIDE*SIDE/2;i>=0;i--){
                if(map[i]==0){
                    if(std::rand()%4==0){
                        map[i]=2;
                        return;
                    }
                }
            }
            for(int i=SIDE*SIDE/2+1;i<SIDE*SIDE;i++){
                if(map[i]==0){
                    if(std::rand()%4==0){
                        map[i]=2;
                        return;
                    }
                }
            }
        }
    }
}

void MainWindow::toleft(){
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
}

void MainWindow::toright(){
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
}

void MainWindow::toup(){
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
}

void MainWindow::todown(){
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
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Up:
        changed=false;
        toup();
        for(int row=1;row<SIDE;row++){
            for(int col=0;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[(row-1)*SIDE+col]);
                if(v!=0){
                    map[(row-1)*SIDE+col]=v;
                    map[row*SIDE+col]=0;
                    changed=true;
                }
            }
        }
        toup();
        rancreate(changed);
        changeLCD(map);
        break;
    case Qt::Key_Down:
        changed=false;
        todown();
        for(int row=SIDE-2;row>=0;row--){
            for(int col=0;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[(row+1)*SIDE+col]);
                if(v!=0){
                    map[(row+1)*SIDE+col]=v;
                    map[row*SIDE+col]=0;
                    changed=true;
                }
            }
        }
        todown();
        rancreate(changed);
        changeLCD(map);
        break;
    case Qt::Key_Left:
        changed=false;
        toleft();
        for(int row=0;row<SIDE;row++){
            for(int col=1;col<SIDE;col++){
                int v=canmerge(map[row*SIDE+col],map[row*SIDE+col-1]);
                if(v!=0){
                    map[row*SIDE+col-1]=v;
                    map[row*SIDE+col]=0;
                    changed=true;
                }
            }
        }
        toleft();
        rancreate(changed);
        changeLCD(map);
        break;
    case Qt::Key_Right:
        changed=false;
        toright();
        for(int row=0;row<SIDE;row++){
            for(int col=SIDE-2;col>=0;col--){
                int v=canmerge(map[row*SIDE+col],map[row*SIDE+col+1]);
                if(v!=0){
                    map[row*SIDE+col+1]=v;
                    map[row*SIDE+col]=0;
                    changed=true;
                }
            }
        }
        toright();
        rancreate(changed);
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

bool MainWindow::checkfinish(){
    changed=false;
    for(int row=1;row<SIDE;row++){
        for(int col=0;col<SIDE;col++){
            int v=canmerge(map[row*SIDE+col],map[(row-1)*SIDE+col]);
            if(v!=0){
                return true;
            }
        }
    }
    for(int row=SIDE-2;row>=0;row--){
        for(int col=0;col<SIDE;col++){
            int v=canmerge(map[row*SIDE+col],map[(row+1)*SIDE+col]);
            if(v!=0){
                return true;
            }
        }
    }
    for(int row=0;row<SIDE;row++){
        for(int col=SIDE-2;col>=0;col--){
            int v=canmerge(map[row*SIDE+col],map[row*SIDE+col+1]);
            if(v!=0){
                return true;
            }
        }
    }
    for(int row=0;row<SIDE;row++){
        for(int col=1;col<SIDE;col++){
            int v=canmerge(map[row*SIDE+col],map[row*SIDE+col-1]);
            if(v!=0){
                return true;
            }
        }
    }
    for(int row=0;row<SIDE;row++){
        for(int col=1;col<SIDE;col++){
            if(map[row*SIDE+col]!=0){
                for(int i=col;i>0;i--){
                    if(map[row*SIDE+i-1]==0){
                        return true;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    for(int row=0;row<SIDE;row++){
        for(int col=SIDE-2;col>=0;col--){
            if(map[row*SIDE+col]!=0){
                for(int i=col;i<SIDE-1;i++){
                    if(map[row*SIDE+i+1]==0){
                        return true;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    for(int row=1;row<SIDE;row++){
        for(int col=0;col<SIDE;col++){
            if(map[row*SIDE+col]!=0){
                for(int i=row;i>0;i--){
                    if(map[(i-1)*SIDE+col]==0){
                        return true;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    for(int row=SIDE-2;row>=0;row--){
        for(int col=0;col<SIDE;col++){
            if(map[row*SIDE+col]!=0){
                for(int i=row;i<SIDE-1;i++){
                    if(map[(i+1)*SIDE+col]==0){
                        return true;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    return false;
}

void MainWindow::on_pushButton_clicked()
{
    initial();
    changeLCD(map);
}

