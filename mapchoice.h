#ifndef MAPCHOICE_H
#define MAPCHOICE_H
#include <QTimer>
#include <QMainWindow>
#include "gamescene.h"
#include "gaming.h"
#include <QtMultimedia>

namespace Ui {
class MapChoice;
}

class MapChoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapChoice(QWidget *parent = nullptr);
    ~MapChoice();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void reshow();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

signals:
    void sendsignal();

private:
    Ui::MapChoice *ui;
    gaming* attMap;
    QMediaPlayer *button;
    QMediaPlayer *background;
};

#endif // MAPCHOICE_H
