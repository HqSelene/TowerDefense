#ifndef GAMING_H
#define GAMING_H
#include <QTimer>
#include <QMainWindow>
#include "gamescene.h"
#include "QMouseEvent"
#include "QMediaPlayer"
namespace Ui {
class gaming;
}

class gaming : public QMainWindow
{
    Q_OBJECT

public:
    explicit gaming(int n,QWidget *parent = nullptr);
    ~gaming();
    void paintEvent(QPaintEvent*e);

protected:
    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);

signals:
    void sendsignal();

private:
    Ui::gaming *ui;
    gameScene world;

    QTimer* TCreateEnemy;
    QTimer* timer;
    static int time;

    QMediaPlayer* Victory;
    QMediaPlayer* Loss;
    QMediaPlayer* background;

private slots:
    void run();
    void create();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

};

#endif // GAMING_H
