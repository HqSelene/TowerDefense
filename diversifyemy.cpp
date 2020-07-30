#include "diversifyemy.h"
#include "data.h"

double distance(Object a,double x,double y){
    double x_dis=a.getPos().x()-x;
    double y_dis=a.getPos().y()-y;
    double s=x_dis*x_dis+y_dis*y_dis;
    return pow(s,0.5);
}

bool Enemy2::setAttack2()
{
    if(isSkillReady())//冷却完成
    {
        if(nowBlood<fullBlood&&nowBlood+ENEMY2_SKILL_BLOOD<=fullBlood&&nowBlood>=10)//2号敌人在一定条件下能够回血
        {
            nowBlood+=ENEMY2_SKILL_BLOOD;
            skillCool();
            return true;
        }
    }
    return false;
}

QPointF Enemy3::setAttack3()
{
    for(int i=0;i<tar3.size();i++)
    {
        if(distance(*tar3[i],getPos().x(),getPos().y())<=SkillRange3)//找到攻击范围内的第一个塔，并将其属性设定为已毁灭
        {
            tar3[i]->setDamage();
            skillCool();
            return tar3[i]->getPos();
        }
    }
    return QPointF(-1,-1);
}

bool Enemy4::setAttack4()
{
    for(int i=0;i<tar4.size();i++)
    {
        if(distance(*tar4[i],getPos().x(),getPos().y())<=SkillRange4)//4号敌人可以使一定范围类的同盟同时瞬移一段距离
        {
            skillCool();
            tar4[i]->setPos(tar4[i]->getPos().x()-upDistance,tar4[i]->getPos().y());
        }
    }
    return true;
}

diversifyEmy::diversifyEmy(int num):enemy(num),Enemy1(num),Enemy2(num),Enemy3(num),Enemy4(num)
{
    switch (getID())
    {
    case 2:
        SkillPic.load("://picture/enemy/backToBlood.png");
        break;
    case 3:
        SkillPic.load("://picture/Weapon/dead_warning.png");
        break;
    case 4:
        SkillPic.load("://picture/enemy/SpeedUp.png");
        break;
    }
}

void diversifyEmy::show(QPainter(*painter))
{
    if(isSkillReady())
    {

        switch (getID())
        {
        case 1:
            break;
        case 2:
        {
            if(setAttack2())
                painter->drawPixmap(Obx-ENEMY/2,Oby+ENEMY/2,ENEMY,ENEMY/3,SkillPic);
        }
            break;
        case 3:
        {
            QPointF tmp=setAttack3();
            if(tmp!=QPointF(-1,-1))
            {
                painter->drawPixmap(tmp.x()-WEAPON,tmp.y()-WEAPON,WEAPON,WEAPON/2,SkillPic);//在即将被敌军消灭的塔上发出警告
            }
        }
            break;
        case 4:
        {
            if(setAttack4())
                painter->drawPixmap(Obx-ENEMY/2,Oby-ENEMY,ENEMY,ENEMY/2,SkillPic);//在发动攻击的敌人头上显示发动技能
        }
            break;
        }
    }
    enemy::show(painter);
}





