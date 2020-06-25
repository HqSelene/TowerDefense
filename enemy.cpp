#include "enemy.h"
#include <QPainter>
#include "data.h"

Blood::Blood():k(0),m(0)
{
    setMinimum(0);
    setMaximum(100);
    fullBlood=QPixmap("://picture/enemy/red blood.jpg");
    bottomBlood =QPixmap("://picture/enemy/white blood.jpg");
    font=QFont("Microsoft YaHei", 15, QFont::Bold);
}

void Blood::show(QPainter(* painter))
{

    QString Str = QString("%1%").arg(QString::number(value()));
    //画血条
    painter->drawPixmap(rect,bottomBlood);
    painter->drawPixmap(fillRect,fullBlood);

    //画文字
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(textRect, Qt::AlignCenter, Str);
}

enemy::enemy(int num):Object(0,0,ENEMY,ENEMY),win(false),nowPath(1),damage(0),Miss(0),skillReady(false)
{
    object=new QPixmap;
    blood=new Blood;
    setID(num);
    damage=false;
    //设置血条
    blood->setRange(0,100);  // 最小值/最大值
    blood->rect = QRect(Obx-BLOODWIDE/2,Oby-40, BLOODWIDE, BLOODHEIGHT);
    switch (num)
    {
        case 1:
        {
            ID=1;
            coin=15;
            attackAbility=1;
            nowBlood=fullBlood=100;
            speed=2;
            object->load("://picture/enemy/1/01_01.jpg");
        }
        break;
    case 2:
    {
        ID=2;
        coin=20;
        attackAbility=1;
        nowBlood=fullBlood=130;
        speed=2.5;
        object->load("://picture/enemy/2/05_01.jpg");
        cooldown=skillInterval=25;
    }
        break;
    case 3:
    {
        ID=3;
        coin=30;
        attackAbility=2;
        nowBlood=fullBlood=120;
        speed=6;
        object->load("://picture/enemy/4/29_00.png");
    }
        break;
    case 4:
    {
        ID=4;
        coin=40;
        attackAbility=3;
        nowBlood=fullBlood=200;
        speed=2;
        object->load("://picture/enemy/5/10_01.png");
    }
    }
}

void enemy::setObject(int st){
    st=st%4;
    switch(ID)
    {
    case 1:{
        switch(st)
        {
        case 0:
            *object=QPixmap("://picture/enemy/1/01_01.jpg");
            break;
        case 1:
            *object=QPixmap("://picture/enemy/1/01_02.jpg");
            break;
        case 2:
            *object=QPixmap("://picture/enemy/1/01_03.jpg");
            break;
        case 3:
            *object=QPixmap("://picture/enemy/1/01_04.jpg");
            break;
        }
    }
        break;
    case 2:
    {
        switch(st)
        {
        case 0:
            *object=QPixmap("://picture/enemy/2/05_01.jpg");
            break;
        case 1:
            *object=QPixmap("://picture/enemy/2/05_02.jpg");
            break;
        case 2:
            *object=QPixmap("://picture/enemy/2/05_03.jpg");
            break;
        case 3:
            *object=QPixmap("://picture/enemy/2/05_04.jpg");
        }
    }
        break;
    case 3:
    {
        switch(st)
        {
        case 0:
            *object=QPixmap("://picture/enemy/4/29_00.png");
            break;
        case 1:
            *object=QPixmap("://picture/enemy/4/29_01.png");
            break;
        case 2:
            *object=QPixmap("://picture/enemy/4/29_02.png");
            break;
        case 3:
            *object=QPixmap("://picture/enemy/4/29_03.png");

        }
    }
        break;
    case 4:
    {
        switch(st)
        {
        case 0:
            *object=QPixmap("://picture/enemy/5/10_01.png");
            break;
        case 1:
            *object=QPixmap("://picture/enemy/5/10_02.png");
            break;
        case 2:
            *object=QPixmap("://picture/enemy/5/10_02.png");
            break;
        case 3:
            *object=QPixmap("://picture/enemy/5/10_04.png");

        }
    }

    }
}

void enemy::show(QPainter* painter){
    //应该要先移动再画

    SetSkill();
    painter->drawPixmap(Obx-wid/2,Oby-hei/2,wid,hei,*object);

    blood->setValue(100*nowBlood/fullBlood);
    double k = (double)blood->value()/100;
    int m = (int)(blood->rect.width() * k);
    //画血条
    blood->fillRect = blood->rect.adjusted(0, 0,m-blood->rect.width(), 0);
    blood->rect.moveTo(Obx-BLOODWIDE/2,Oby-40);
    blood->fillRect.moveTo(Obx-BLOODWIDE/2,Oby-40);
    blood->textRect=QRect(Obx-BLOODWIDE/2,Oby-75,60,15);
    blood->show(painter);

}

void enemy::attack(double bl)
{
    if(bl<0)
    {
        Obx-=bl;
        nowBlood+=bl/2;
        return;
    }
    if(ID==2)
    {
        if(isSkillReady())
        {
            Miss=1;
            skillCool();
            return;
        }
    }
    nowBlood-=bl;
    if(nowBlood<=0)
    {
        damage=true;
    }

}
void enemy::CoolDown(){//冷却
    if(Miss!=0)
        return;
    cooldown =cooldown- 1.0/INTERVAL;
    if(cooldown < 0 ){
        skillReady = true;
        cooldown = skillInterval;
    }
}

void enemy::SetSkill()
{
    switch(ID)
    {
    case 1:
        break;
    case 2:
    {
        if(Miss!=0)
        {
            if(Miss==1)
            {
                Oby-=20;
                Obx-=40;
            }
            Miss++;
        }
        else if(Miss==15)
        {
            Oby+=20;
            Miss=0;
            cooldown = skillInterval;
        }
    }
        break;
    case 3:
    {

    }
        break;
    }
}
