#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSound>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),window(nullptr)
{
    ui->setupUi(this);
    setFixedSize(MAPWIDE,MAPHEIGHT);

    backgroundMusic = new QMediaPlayer;//创建播放器
    backgroundMusic->setMedia(QUrl("qrc:/picture/music/Beethoven Virus.mp3"));
    backgroundMusic->setVolume(50);
    button1=new QMediaPlayer;
    button1->setMedia(QUrl("qrc:/picture/music/403014__inspectorj__ui-confirmation-alert-b4.wav"));
    button1->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent*)
{
    backgroundMusic->play();
    QPainter *p = new QPainter();
    p->begin(this);
    QPixmap background("://picture/backLogin.jpg");
    p->drawPixmap(0,0,MAPWIDE,MAPHEIGHT,background);
    p->end();
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::hide();
    window=new MapChoice;
    backgroundMusic->stop();
    button1->play();
    connect(window,SIGNAL(sendsignal()),this,SLOT(reshow()));
    window->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::reshow()
{
    this->show();
}
