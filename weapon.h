
#ifndef WEAPON_H
#define WEAPON_H
#include"object.h"
#include"enemy.h"
#include <QPainter>
#include <QVector>
class Weapon:public Object
{
public:
    Weapon(int num,int mouse_x,int mouse_y);

    //武器需要的金币
    int getDamage(){return damage;}
    int getMoney(int i){return levelCoin[i];}
    int getlevel(){return level;}
    double getrange(){return attackRange[level];}
    int getInjury(){return injury[level];}
    //void handleCoolDown();//此功能可以移交Scene也可以不移交
    void fireCool(){fireReady = false;cooldown = fireInterval[level];}//开火后重置属性

   // void setIsFireReady(bool re){fireReady = re;}

    bool isFireReady(){return fireReady;}//判断是否可以开火
    void upLevel();//升级并判断是否成功
    void CoolDown();

    QVector<enemy*> attack_target;//攻击对象


private:
    int level;
    bool damage;

    bool fireReady;
    double* attackRange;//侦测范围
    double* fireInterval;//开火时间间隔
    int* injury;

    double cooldown;

    QPixmap* levelWeapon;//不同级别的图案可能不同，不一定，暂时放着
    int* levelCoin;//不同级别需要的金币
};

#endif // WEAPON_H
