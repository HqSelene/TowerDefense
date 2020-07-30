#ifndef DIVERSIFYEMY_H
#define DIVERSIFYEMY_H
#include "enemy.h"
#include "QPainter"
#include "weapon.h"
class Enemy1:virtual public enemy
{
public:
    Enemy1(int num):enemy(num){}
};

class Enemy2:virtual public enemy
{
public:
    Enemy2(int num):enemy(num){}//有回血的技能
    bool setAttack2();
};

class Enemy3:virtual public enemy
{
    double SkillRange3;
protected:
    QVector<Weapon*> tar3;
public:
    Enemy3(int num):enemy(num),SkillRange3(150){}
    void receiveWpn(QVector<Weapon*>& a){tar3=a;}//能够攻击一个塔
    QPointF setAttack3();
};

class diversifyEmy;

class Enemy4:virtual public enemy
{
    int upDistance;//使敌军位移的距离
    double SkillRange4;
protected:
    QVector<diversifyEmy*> tar4;
public:
    Enemy4(int num):enemy(num),upDistance(30),SkillRange4(250){}
    void receiveEmy(QVector<diversifyEmy*>& a){tar4=a;}
    bool setAttack4();
};

class diversifyEmy:public Enemy1,public Enemy2,public Enemy3,public Enemy4
{
    QPixmap SkillPic;
public:
    diversifyEmy(int num);
    void show(QPainter* painter);
};

#endif // DIVERSIFYEMY_H
