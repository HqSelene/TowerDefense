#include "enemy.h"
#ifndef SKILLOFENEMY_H
#define SKILLOFENEMY_H

class SkillOfEnemy:public enemy
{
protected:
    double cooldown;
    bool skillReady;
    double skillInterval;

public:
    bool isSkillReady(){return skillReady;}
    void skillCool(){skillReady = false;cooldown = skillInterval;}
    void CoolDown();
    void attack(double bl){nowBlood-=bl;if(nowBlood<=0){damage=true;}}

    SkillOfEnemy(int num);
};

class Skill1:public SkillOfEnemy
{
public:
    Skill1():SkillOfEnemy(1){}
    void attack(double bl){SkillOfEnemy::attack(bl);}
};

class Skill2:public SkillOfEnemy
{
public:
    Skill2():SkillOfEnemy(2){}
    int miss;
    void show(QPainter*painter);
    void attack(double bl);

};
#endif // SKILLOFENEMY_H
