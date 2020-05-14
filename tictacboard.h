#ifndef TICTACBOARD_H
#define TICTACBOARD_H
#include <QApplication>
#include "tictacbutton.h"
#include <QGridLayout>
#include <QPalette>

class TicTacBoard: public QWidget{
    Q_OBJECT
public:
    TicTacBoard(int n, QWidget *parent = 0,const char * name = 0);
    ~TicTacBoard();
    enum STATE{INIT,PLAYER1,PLAYER1_WON, PLAYER2, PLAYER2_WON, DRAW};
    STATE State() const {return st;}
    void player2Starts(bool v);
    void newGame();
signals:
    void finished();
 private slots:
    void buttonClicked();
private:
    STATE st;
    void setState(STATE state){st=state;}
    void updateButtons();
    int checkBoard(TicTacArray *);
    void player2Move();
    int nBoard;
    bool player2_starts;
    TicTacArray *array;
    TicTacButton *button;

};

#endif // TICTACBOARD_H
