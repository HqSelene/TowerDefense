#include "gaming.h"
#include "ui_gaming.h"
#include <QMessageBox>
#include <QTime>

int gaming::time=0;

gaming::gaming(int n,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gaming)
{
    ui->setupUi(this);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//每次生成不同的随机数

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(MAPWIDE, MAPHEIGHT);

    world.setScene(n);
    timer=new QTimer;
    TCreateEnemy=new QTimer;
    timer->start(20);
    TCreateEnemy->start(world.frequency);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    connect(TCreateEnemy, SIGNAL(timeout()), this, SLOT(create()));

    background=new QMediaPlayer;
    background->setMedia(QUrl("qrc:/picture/music/The Dawn.mp3"));
    background->setVolume(50);
    background->play();

    Loss=new QMediaPlayer;
    Loss->setMedia(QUrl("qrc:/picture/music/415209__inspectorj__cat-screaming-a.wav"));
    Loss->setVolume(50);

    Victory=new QMediaPlayer;
    Victory->setMedia(QUrl("qrc:/picture/music/466133__humanoide9000__victory-fanfare.wav"));
    Victory->setVolume(50);
}

gaming::~gaming()
{
    delete ui;
}

void gaming::mousePressEvent(QMouseEvent* e){
    world.SingleClick(e);
}


void gaming::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_A)
    {
        QMessageBox message(QMessageBox::NoIcon,"Instructions", "Key_1:tower 1  Key_2:tower 2  Key_3:tower3   Key_A:Instructions  Key_D:delete");
        message.setIconPixmap(QPixmap("://picture/ins.png"));
        message.exec();
        //调用说明书
    }
    else if(e->key()==Qt::Key_D)
        world.deleteTower();
    else
        world.setTower(e);
}


void gaming::paintEvent(QPaintEvent *e)
{
    if(!world.isWarEnd()&&!world.ifWin())
    {
        background->stop();
        Loss->play();
        TCreateEnemy->stop();
        timer->stop();
        QMessageBox message(QMessageBox::NoIcon,"Warn", "YOU FAILED!    HUMAN WILL DIE SOON");
        message.setIconPixmap(QPixmap("://picture/bad_end.jpg"));
        message.exec();
        Loss->stop();
        emit sendsignal();
        this->close();
    }
    else if(world.ifWin()&&!world.isWarEnd())
    {
        background->stop();
        Victory->play();
        TCreateEnemy->stop();
        timer->stop();
        QMessageBox message(QMessageBox::NoIcon,"Warn", "You WIN!  Let go to the next battlefield");

        message.setIconPixmap(QPixmap("://picture/happy_end.jpg"));
        message.exec();
        Victory->stop();
        emit sendsignal();
        this->close();
    }
    else
    {
        QPainter *p = new QPainter();
        p->begin(this);
        this->world.show(p);
        p->end();
        delete p;
    }
}

void gaming::run()
{
    gameScene::st++;
    if(!world.isWarEnd())
    {
        background->stop();
        TCreateEnemy->stop();
        timer->stop();
    }
}

void gaming::create()
{
    world.Create();
}

void gaming::on_pushButton_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Delete", "Do you want to bak to the map?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb==QMessageBox::Yes)
    {
        background->stop();
        emit sendsignal();
        this->close();
    }

}

void gaming::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Delete", "Are you sure to end this game?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb==QMessageBox::Yes)
    {
        TCreateEnemy->stop();
        timer->stop();
        background->stop();
        QApplication* app;
        app->exit(0);
    }

}

void gaming::on_pushButton_3_clicked()
{
    timer->stop();
    TCreateEnemy->stop();
}

void gaming::on_pushButton_4_clicked()
{
    timer->start();
    TCreateEnemy->start();
}

