#include "skillofenemy.h"

SkillOfEnemy::SkillOfEnemy(int num):enemy(num)
{

}


void Skill2::attack(double bl)
{
    if(isSkillReady())
    {
        Miss=1;
        skillCool();
        return;
    }
    nowBlood-=bl;
    if(nowBlood<=0)
    {
        damage=true;
    }

}

void Skill2::show(QPainter* painter)
{
    if(Miss!=0)
    {
        Obx+=20;
        Miss++;
    }
    if(Miss==4)
    {
        Obx=Obx-20-speed;
        Miss=0;
    }

    enemy::show(painter);
}
