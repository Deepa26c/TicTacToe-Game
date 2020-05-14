#ifndef TICTACBUTTON_H
#define TICTACBUTTON_H
#include <QPushButton>
#include <QVector>
#include <QArrayData>

class TicTacButton: public QPushButton{
    Q_OBJECT
public:
    TicTacButton(QWidget *parent);
    enum Type {EMPTY, CIRCLE, CROSS};
    Type type() const {return t;}
    void setType(Type type){
        t = type;
        repaint();
    }
    QSizePolicy sizepolicy() const{
        return QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    QSize size() const {
        return QSize(32,32);
    }
    QSize minSize() const{
        return QSize(10,10);
    }
protected:
    void drawButtonLabel(QPainter *);
private:
    Type t;

};

typedef QVector<TicTacButton>        TicTacButtons;
typedef QArrayDataPointerRef<int*>          TicTacArray;



#endif // TICTACBUTTON_H
