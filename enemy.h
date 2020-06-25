#ifndef ENEMY_H
#define ENEMY_H
#include"object.h"
#include "map.h"
#include <QProgressBar>
class Blood:public QProgressBar
{
private:
    QPixmap fullBlood,bottomBlood;
    QFont font;
public:
    int k;
    double m;
    QRect rect;
    QRect fillRect;
    QRect textRect;

    Blood();

    void show(QPainter* painter);

};

class enemy:public Object
{
public:
    enemy(int num);

    void show(QPainter* painter);
    void attack(double bl);//受到攻击
    void setObject(int st);//移动过程中不断的走

    bool isSkillReady(){return skillReady;}
    bool isDamage(){return damage;}
    void skillCool(){skillReady = false;}

    int getBlood(){return nowBlood;}
    int getAttakAbility(){return attackAbility;}
    int getCoin(){return coin;}
    int getPath(){return nowPath;}
    int getSpeed(){return speed;}
    void setPath(){nowPath++;}
    bool win;

    void SetSkill();
    void CoolDown();

private:
    int Miss;//判断是否躲避成功
    int attackAbility;//攻击能力
    int coin;//被杀死之后可以得到的金币
    int nowPath;//目前所在道路
    double speed;
    double fullBlood,nowBlood;//设置血量

    bool damage;
    Blood* blood;

    double cooldown;
    bool skillReady;
    double skillInterval;
};

#endif // ENEMY_H
