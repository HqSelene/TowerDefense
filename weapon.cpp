

#include "weapon.h"
#include"data.h"

Weapon::Weapon(int num,int mouse_x,int mouse_y):Object(mouse_x,mouse_y,WEAPON,WEAPON),level(0),damage(false),fireReady(false)
{
    setID(num);
    object=new QPixmap;
    switch(num)
    {
    case 1:
    {
        levelCoin=new int[3]{50,65,80};
        attackRange=new double[3]{WEAPON_RANGE_1,WEAPON_RANGE_1+50,WEAPON_RANGE_1+100};
        fireInterval=new double[3]{WEAPON_INTERVAL_1,WEAPON_INTERVAL_1-0.02,WEAPON_INTERVAL_1-0.04};
        injury=new int[3]{10,12,14};
        object->load("://picture/Weapon/1/base1n.png");
        levelWeapon=new QPixmap[2];
        levelWeapon[0].load("://picture/Weapon/1/base2n.png");
        levelWeapon[1].load("://picture/Weapon/1/base3n.png");
    }
        break;
    case 2:
    {
        levelCoin=new int[3]{62,80,98};
        attackRange=new double[3]{WEAPON_RANGE_2,WEAPON_RANGE_2+50,WEAPON_RANGE_2+50};
        fireInterval=new double[3]{WEAPON_INTERVAL_2,WEAPON_INTERVAL_2-0.02,WEAPON_INTERVAL_2-0.04};
        injury=new int[3]{-30,45,60};
        object->load("://picture/Weapon/2/WB_base_d0");
        levelWeapon=new QPixmap[2];
        levelWeapon[0].load("://picture/Weapon/2/WB_baseu2_d0.png");
        levelWeapon[1].load("://picture/Weapon/2/WB_baseu3_d0.png");
    }
        break;
    }
    cooldown=fireInterval[0];
}


void Weapon::CoolDown(){//冷却
    cooldown =cooldown- 1.0/INTERVAL;
    if(cooldown < 0 ){
        fireReady = true;
        cooldown = fireInterval[level];
    }
}


void Weapon::upLevel(){//升级功能
    level++;
    *this->object=levelWeapon[level-1];
    cooldown = fireInterval[level];
}
