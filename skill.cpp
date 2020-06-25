#include "skill.h"

Skill::Skill(int num,QPointF tar,Weapon* a):Object(a->getPos().x(),a->getPos().y(),SKILL,SKILL),target(tar),damage(false)
{
    length=0;
    object_ID=num;
    switch (num)
    {
    case 1:
    {
        object->load("://picture/Weapon/1/bullet1.PNG");
        damageAB=a->getInjury();
        range=a->getrange();
        speed=50;
    }
        break;
    case 2:
    {
        {
            object->load("://picture/Weapon/2/bullet2.png");
            damageAB=a->getInjury();
            range=a->getrange();
            speed=12;
        }
    }
    }

    double tmp=sqrt(powf(tar.x()-getPos().x(),2)+powf(tar.y()-getPos().y(),2));
    cosx=(tar.x()-getPos().x())/tmp;
    sinx=(tar.y()-getPos().y())/tmp;

}

void Skill::show(QPainter *p)
{
    p->drawPixmap(getPos().x()-SKILL/2,getPos().y()-SKILL/2,wid,hei,*object);
}

void Skill::move()
{
    length+=speed;
    this->setPos(getPos().x()+speed*cosx,getPos().y()+speed*sinx);
    if(length>range)
    {
        damage=true;
    }
    if((cosx>=0&&getPos().x()>target.x())||(cosx<=0&&getPos().x()<target.x()))
    {
        damage=true;
    }
}

bool Skill::attWin(QPointF a)
{
    if(sqrt(pow(a.x()-getPos().x(),2)+pow(a.y()-getPos().y(),2))< ENEMY/2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

