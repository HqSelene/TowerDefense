#ifndef SKILL_H
#define SKILL_H
#include "weapon.h"
#include "enemy.h"
#include "object.h"
#include "data.h"
//完成其中的一些特效

class Skill:public Object
{
public:
    Skill(int num,QPointF tar,Weapon* a);

    int getDamage(){return damageAB;}
    int getSpeed(){return speed;}

    bool attWin(QPointF a);
    bool getDM(){return damage;}

    void setDamage(){damage=true;}
    void show(QPainter* painter);
    void move();

private:
    const int object_ID;

    bool damage;
    int damageAB;
    double cosx,sinx;
    int speed;

    double range;//攻击范围
    QPointF target;//攻击目标点
    double length;//行走路程是否超过范围
};




#endif // SKILL_H
