#include <tictacbutton.h>
#include <QApplication>
#include <QPainter>
#include <QCheckBox>
#include <qdrawutil.h>
#include <QCheckBox>
#include <QLabel>
#include <QLayout>
#include <QPen>


TicTacButton::TicTacButton(QWidget *parent):QPushButton(parent)
{
    t = EMPTY;
}

void TicTacButton::drawButtonLabel(QPainter *p){
    QRect r = rect();
    p->setPen(QPen(QColor(Qt::red),2));

    if(t == CIRCLE)
    {
        p->drawEllipse(r.left()+4,r.top()+4,r.width()-8,r.height()-8);
    }
    else if(t == CROSS)
    {
        p->drawLine(r.topLeft() +QPoint(4,4), r.bottomRight() -QPoint(4,4));
        p->drawLine(r.bottomLeft() +QPoint(4,-4), r.topRight() -QPoint(4,-4));
    }
}
