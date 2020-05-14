#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QInputDialog>
#include <QTextItem>
#include <QMessageBox>
#include <iostream>
#include <QObject>
#include <QPaintEvent>
#include <iostream>
#include <QActionEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(500,500);

    rects[0] = QRect(50,100,100,100);
    rects[1] = QRect(150,100,100,100);
    rects[2] = QRect(250,100,100,100);
    rects[3] = QRect(50,200,100,100);
    rects[4] = QRect(150,200,100,100);
    rects[5] = QRect(250,200,100,100);
    rects[6] = QRect(50,300,100,100);
    rects[7] = QRect(150,300,100,100);
    rects[8] = QRect(250,300,100,100);

    lines[0] = QLine(50,150,350,150);
    lines[1] = QLine(100,100,100,400);
    lines[2] = QLine(50,250,350,250);
    lines[3] = QLine(200,100,200,400);
    lines[4] = QLine(50,350,350,350);
    lines[5] = QLine(300,100,300,400);
    lines[6] = QLine(50,100,350,400);
    lines[7] = QLine(350,100,50,400);
    lineToDraw = -1;
   moves = 0;
   for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           arr[i][j] = 0;
       }
   }

   connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(onActionExit()));
 //  connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(onActionNew()));
  // connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(onActionSettings()));
   modeList<<"2 Players"<<"Player1 vs Computer"<<"Computer vs Player2";
   this->show();
   mode= QInputDialog::getItem(this,"Choose number of players", "Game Mode:",modeList,0,false,&ok);
   if(!ok)
       this->close();
   if(mode.compare("computer vs Player2")==0)
       robotMove();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch(e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *p){
    QPainter *painter = new QPainter(this);
    painter->fillRect(this->rect(),QColor("black"));
    painter->setPen(QColor("green"));
    painter->drawRects(rects,9);
    painter->setFont(QFont("Courier New",50,1,false));
    for(int i=0;i<3;i++){
        for(int u=0;u<3;u++){
            if(arr[i][u]==1)
                painter->drawPixmap(rects[i*3+u].x()+15,rects[i*3+u].y()+15,QPixmap(":/Images/cross.png"));
            else if(arr[i][u]==2)
                painter->drawPixmap(rects[i*3+u].x()+15,rects[i*3+u].y()+15,QPixmap(":/Images/flower.png"));
        }
    }
    if(lineToDraw > -1){
        painter->setPen(QPen(QBrush(QColor("red")),10));
        painter->drawLine(lines[lineToDraw]);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *m){
    for(int i=0;i<9;i++){
        if(rects[i].contains(m->pos())){
            int row = i/3;
            int col = i%3;
            if(arr[row][col]==0){
                moves++;
                int player = moves%2 ==1 ? 1 : 2;
                arr[row][col]=player;

                repaint(rects[i]);
                if(check()){
                    repaint();

                    QString text = "Player"+QString::number(player)+"wins, Restart?";
                    int btn=QMessageBox::question(this,"Game Over",text,QMessageBox::Ok,QMessageBox::Close);
                    if(btn == QMessageBox::Ok)
                        onActionNew();
                    else if(btn == QMessageBox::Close)
                        this->close();
                    return;
                }
                else if(moves==9){
                    QString text = "Draw, Restart?";
                    int btn = QMessageBox::question(this,"Game Over",text,QMessageBox::Ok,QMessageBox::Close);
                    if(btn==QMessageBox::Ok) onActionNew();
                    else if(btn==QMessageBox::Close) this->close();
                    return;
                }
                if(mode.compare("2 Players")!=0) robotMove();
            }
            return;
        }
    }
}

void MainWindow::onActionExit(){
    this->close();
}

void MainWindow::onActionNew(){
    mode = QInputDialog::getItem(this,"Choose no:of players","Game Mode: ",modeList,0,false,&ok);
    if(!ok) this->close();
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            arr[i][j] = 0;
    moves =0;
    lineToDraw = -1;
    repaint();
    if(mode.compare("Computer vs Player1")==0) robotMove();
}

bool MainWindow::check(){
    for(int i=0;i<3;i++)
    {
        if(arr[i][i]==0)continue;
        else if(arr[i][0]==arr[i][1]&&arr[i][1]==arr[i][2])
        {
            lineToDraw = i*2;
            return true;
        }
        else if(arr[0][i]==arr[1][i]&&arr[1][i]==arr[2][i])
        {
            lineToDraw = i*2+1;
            return true;
        }
    }
    if(arr[0][0]==arr[1][1]&&arr[1][1]==arr[2][2]&&arr[2][2]!=0)
    {
        lineToDraw =6;
        return true;
    }
    if(arr[0][2]==arr[1][1]&&arr[1][1]==arr[2][0]&&arr[2][0]!=0)
    {
        lineToDraw =7;
        return true;
    }
    return false;
}

QString MainWindow::defence(){
    int y;
    if(mode.compare("Computer vs Players1")==0)
    {
        y=2;
    }
    else
    {
        y=1;
    }
    int row,col=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            row = row+(arr[i][j]==y ? 1: 0);
            col = col+(arr[i][j]==y ? 1: 0);
        }
        if(row==2)
            for(int j=0;j<3;j++)
                if(arr[i][j]==0) return QString::number(i).append(QString::number(j));
        if(col==2)
            for(int j=0;j<3;j++)
                if(arr[i][j]==0) return QString::number(j).append(QString::number(i));
        row=0;
        col=0;
    }
    row = row+arr[0][0]==y?1:0;
    row = row+arr[1][1]==y?1:0;
    row = row+arr[2][2]==y?1:0;
    row = row+arr[0][2]==y?1:0;
    row = row+arr[1][1]==y?1:0;
    row = row+arr[2][0]==y?1:0;
    if(row==2)
        for(int i=0;i<3;i++)
            if(arr[i][i]==0)return QString::number(i).append(QString::number(i));
    if(col==2)
        for(int i=0;i<3;i++)
            if(arr[i][2-i]==0)return QString::number(i).append(QString::number(2-i));
    return "";
}

QString MainWindow::attack(){
    int x;

    if(mode.compare("Computer vs Player2")==0)
    {
        x=1;
    }
    else
    {
        x=2;
    }

    int row,col=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            row = row+(arr[i][j]==x?1:0);
            col = col+(arr[j][i]==x?1:0);
        }
        if(row==2)
            for(int j=0;j<3;j++)
                if(arr[i][j]==0) return QString::number(i).append(QString::number(j));
        if(col==2){
            for(int j=0;j<3;j++)
                if(arr[j][i]==0) return QString::number(j).append(QString::number(i));
        }
        row=0,col=0;
    }
    row=row+arr[0][0]==x?1:0;
    row=row+arr[1][1]==x?1:0;
    row=row+arr[2][2]==x?1:0;

    col=col+arr[0][2]==x?1:0;
    col=col+arr[1][1]==x?1:0;
    col=col+arr[2][0]==x?1:0;

    if(row==2)
    {
        for(int i=0;i<3;i++)
            if(arr[i][i]==0) return QString::number(i).append(QString::number(i));
    }
    if(col==2)
    {
        for(int i=0;i<3;i++)
            if(arr[i][2-i]==0) return QString::number(i).append(QString::number(2-i));
    }

    return "";


}

void MainWindow::robotMove(){
    int x,y;
    if(mode.compare("computer vs Player1")==0){x=1;}
    else{x=2;}
    if(moves==0){arr[0][0]=x;}
    else if(moves==1){
        if(arr[0][0]==0) arr[0][0]=x;
        else arr[2][0]=x;
    }
    else if(moves==2){
        if(arr[2][2]==0) arr[2][2]=x;
        else arr[2][0]=x;
    }
    else if(moves==3){
        QString str= defence();
        if(!str.isEmpty()){
            arr[str[0].digitValue()][str[1].digitValue()]==x;
        }
        else if(arr[0][2]==0) arr[0][2] = x;
        else arr[2][0]=x;
    }
    else{
        QString str = attack();
        QString str2 =defence();
        if(!str.isEmpty()){arr[str[0].digitValue()][str[1].digitValue()]=x;}
        else if(!str2.isEmpty()){arr[str2[0].digitValue()][str2[1].digitValue()]=x;}
        else if(arr[0][0]==arr[2][2] && arr[2][2]==x && (arr[2][0]==0||arr[0][2]==0)){
            if(arr[2][0]==0) arr[2][0]=x;
            else if(arr[0][2]==0) arr[0][2]=x;
        }
        else if(arr[0][2]==arr[2][0]&& arr[2][0]==x && (arr[0][0]==0||arr[2][2]==0)){
            if(arr[0][0]==0) arr[0][0]=x;
            else if(arr[2][2]==0) arr[2][2]=x;
            }
            else{
                for(int i=0;i<3;i++)
                    for(int j=0;j<3;j++){
                        if(arr[i][j]==0){arr[i][j]=x; i=3; j=3;}
                    }
            }
    }
        moves++;
        repaint();
        if(check()){
            repaint();

            QString text = "Computer wins, restart?";
            int btn=QMessageBox::question(this,"Game Over",text,QMessageBox::Ok,QMessageBox::Close);
            if(btn==QMessageBox::Ok) onActionNew();
            else if(btn==QMessageBox::Close) this->close();
        }

        else if(moves ==9 ){
        QString text = "Draw , Restart?";
        int btn=QMessageBox::question(this,"Game Over",text,QMessageBox::Ok,QMessageBox::Close);
        if(btn==QMessageBox::Ok) onActionNew();
        else if(btn==QMessageBox::Close) this->close();
        return;
        }

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
