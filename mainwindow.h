#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mapchoice.h"
#include <QMainWindow>
#include "data.h"
#include <QPainter>
#include <QtMultimedia>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*e);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void reshow();

signals:
    void sendsignal();

private:
    QMediaPlayer *backgroundMusic;
    QMediaPlayer *button1;

    Ui::MainWindow *ui;
    MapChoice* window;

};
#endif // MAINWINDOW_H
