#include "tictacbutton.h"
#include "tictacboard.h"
#include <QApplication>

TicTacBoard::TicTacBoard(int n, QWidget *parent, const char *name):QWidget(parent)
{
    st = INIT;
    nBoard = n;
    n=n*n;
    player2_starts = false;
    button = new TicTacButton(n);
    array = new TicTacArray(n);
    QGridLayout * grid = new QGridLayout( this,nBoard,nBoard, 4 );
    QPalette p(Qt::blue );

}
