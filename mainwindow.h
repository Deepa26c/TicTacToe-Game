#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
    class QRect;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool check();
    void robotMove();
    QString defence();
    QString attack();
public slots:
    void onActionExit();
    void onActionNew();
protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *p);
    void mousePressEvent(QMouseEvent *m);
private slots:
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QRect rects[9];
    QLine lines[8];
    int activeRect;
    int moves;
    int arr[3][3];
    QString mode;
    QStringList modeList;
    bool ok;
    int lineToDraw;
};
#endif // MAINWINDOW_H
