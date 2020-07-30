#include "mapchoice.h"
#include "ui_mapchoice.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include"gamescene.h"
#include "mainwindow.h"

MapChoice::MapChoice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapChoice),attMap(nullptr)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    ui->setupUi(this);
    setMouseTracking(true);
    setFixedSize(MAPWIDE, MAPHEIGHT);

    button=new QMediaPlayer;
    button->setMedia(QUrl("qrc:/picture/music/403009__inspectorj__ui-confirmation-alert-b3.wav"));
    button->setVolume(50);
    background=new QMediaPlayer;
    background->setMedia(QUrl("qrc:/picture/music/The Dawn.mp3"));
    background->setVolume(50);
    background->play();
}

MapChoice::~MapChoice()
{
    delete ui;
}


void MapChoice::on_pushButton_clicked()
{
    background->stop();
    button->play();
    this->hide();
    QMessageBox message(QMessageBox::NoIcon, "Ready for Round ONE", "Start new journey! Are you ready?");
    message.setIconPixmap(QPixmap("://picture/cat2.png"));
    message.exec();
    attMap=new gaming(1);
    connect(attMap,SIGNAL(sendsignal()),this,SLOT(reshow()));
    attMap->show();
}


void MapChoice::on_pushButton_2_clicked()
{
    background->stop();
    emit sendsignal();
    this->close();
}

void MapChoice::reshow()
{
    background->play();
    this->show();
}

void MapChoice::on_pushButton_3_clicked()
{
    background->stop();
    button->play();
    this->hide();
    QMessageBox message(QMessageBox::NoIcon, "Ready for Round TWO", "Start new journey! Are you ready?");
    message.setIconPixmap(QPixmap("://picture/cat2.png"));
    message.exec();
    attMap=new gaming(2);
    connect(attMap,SIGNAL(sendsignal()),this,SLOT(reshow()));
    attMap->show();
}

void MapChoice::on_pushButton_4_clicked()
{
    background->stop();
    button->play();
    this->hide();
    QMessageBox message(QMessageBox::NoIcon, "Ready for Round THREE", "Last war of destiny!Are you ready?");
    message.setIconPixmap(QPixmap("://picture/cat2.png"));
    message.exec();
    attMap=new gaming(3);
    connect(attMap,SIGNAL(sendsignal()),this,SLOT(reshow()));
    attMap->show();
}
