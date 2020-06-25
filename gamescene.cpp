#include "gamescene.h"
#include "data.h"
#include <math.h>
#include <QString>
#include <QMessageBox>

int gameScene::st=0;
gameScene::gameScene():frequency(0),enemyNum(0),attackNum(0),ifCreate(true),WarNotEnd(true),winOfHuman(false)
{
    nowMap=new Map;
    Coin=new QPixmap("://picture/coin.png");
    life=new QPixmap("://picture/stone.png");
}

void gameScene::setScene(int n)
{
    switch(n)
    {
    case 1:
    {
        frequency=10000;
        nowMap=new Map(1);
        lifePower=1;
        sumOFCoins=150;
    }
        break;
    case 2:
    {
        frequency=10000;
        nowMap=new Map(2);
        lifePower=2;
        sumOFCoins=200;
    }
        break;
    }
}

void gameScene::show(QPainter* painter)
{

    nowMap->show(painter);
    Check();
    findEnemy();//寻找敌人
    attackEnemy();

    Move();
    CreateSkill();
    CreateEnemy();//制造敌人
    painter->drawPixmap(0,MAPHEIGHT-SMALLWEAPON*1.4,SMALLWEAPON*2,SMALLWEAPON*2.3,QPixmap("://picture/SmallWeapon.png"));
    //删除敌人和子弹

    WinOfEnemy();
    if(WarNotEnd)
    {
        for(int i=0;i<enemies.size();i++)
        {
            enemies[i]->setObject(st);
            enemies[i]->show(painter);
            enemies[i]->CoolDown();
        }
        for(int i=0;i<towers.size();i++)
        {
            towers[i]->show(painter);
            towers[i]->CoolDown();
        }
        for(int i=0;i<skills.size();i++)
        {
            skills[i]->show(painter);
        }
    }

    QString str1=QString::number(lifePower,10);
    QString str2=QString::number(sumOFCoins,10);
    QString str3="Attack wave "+QString::number(attackNum,10)+" / "+QString::number(nowMap->allAttack[1],10);
    painter->setPen(Qt::white);
    painter->drawPixmap(30,30,SIZE,SIZE,*life);
    painter->drawText(40+SIZE,30,str1);
    painter->drawPixmap(30,65,SIZE,SIZE,*Coin);
    painter->drawText(40+SIZE,65,str2);

    painter->setFont(QFont("Microsoft YaHei", 20, QFont::Bold));
    painter->drawText(MAPWIDE/2-30,30,str3);
}

void gameScene::CreateEnemy(){
    if(!ifCreate)
        return;
    int a,b;
    enemy* tmp;
    b=qrand()%4+1;//每次生成的敌人个数不超过4
    if(enemyNum+b>nowMap->allAttack[1]*nowMap->allAttack[2])
    {
        b=nowMap->allAttack[1]-enemyNum;//进攻敌人是否结束
    }

    for(int i=0;i<b;i++)
    {
        a=qrand()%nowMap->allAttack[0]+1;//设置生成的敌人种类，根据case数控制敌人出现频率
        switch (a)
        {
        case 1:
            tmp=new enemy(1);
            break;
        case 2:
            tmp=new enemy(2);
            break;
        case 3:
            tmp=new enemy(3);
            break;
        case 4:
            tmp=new enemy(4);
            break;
        }
        tmp->setPos(nowMap->paths[0].sx,nowMap->paths[0].sy);
        enemies.push_back(tmp);
    }
    enemyNum+=b;
    attackNum=enemyNum/nowMap->allAttack[2]+1;
    ifCreate=false;
}


void gameScene::SingleClick(QMouseEvent* e)//处理鼠标点击
{
    QPointF* a=new QPointF(e->x(),e->y());
    processTower.push_back(a);

}

void gameScene::setTower(QKeyEvent *e)
{
    if(processTower.size()==0)
        return;
    int f=1,p=processTower.size()-1;
    for(int i=0;i<towers.size();i++)
    {
        if(distance(Object(processTower.at(p)->x(),processTower.at(p)->y()),*towers[i])<=TILESET/2)
        {
            f=0;
            QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Uplevel", "Do you want to uplevel this weapon", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb==QMessageBox::Yes)
            {
                if(towers[i]->getlevel()<2&&sumOFCoins>towers[i]->getMoney(towers[i]->getlevel()+1))
                {
                    towers[i]->upLevel();
                    sumOFCoins-=towers[i]->getMoney(towers[i]->getlevel());
                }
                else
                {
                    QMessageBox::warning(NULL, "warning", "SORRY,YOU CAN'T UPLEVEL!");
                }
            }
            break;
        }
    }

    if(f)
    {
        int num=0;
        if(e->key()==Qt::Key_1)
        {
            num=1;
        }
        else if(e->key()==Qt::Key_2)
        {
            num=2;
        }
        else if(e->key()==Qt::Key_3)
        {
            num=3;
        }
        if(num==0)
            return;

        Weapon* tmp=new Weapon(num,processTower.at(p)->x(),processTower.at(p)->y());
        if(sumOFCoins<tmp->getMoney(0)){
            //金币不足
            QMessageBox::warning(NULL, "warning", "RUN OUT OF MONEY!");
            return;
        }
        towers.push_back(tmp);
        sumOFCoins-=tmp->getMoney(0);
    }
    processTower.erase(processTower.begin()+0);
}

void gameScene::deleteTower()//玩家删除塔操作
{
    if(processTower.size()==0)
        return;
    int p=processTower.size()-1;
    for(int i=0;i<towers.size();i++)
    {
        if(distance(Object(processTower.at(p)->x(),processTower.at(p)->y()),*towers[i])<=TILESET/2)
        {
            QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Delete", "Do you want to delete this weapon?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb==QMessageBox::Yes)
            {
                sumOFCoins+=towers[i]->getMoney(towers[i]->getlevel())/2;
                delete towers[i];
                towers.erase(towers.begin()+i);
            }
        }
    }
    processTower.erase(processTower.begin()+0);
}


double gameScene::distance(Object a, Object b){
    double x_dis=a.getPos().x()-b.getPos().x();
    double y_dis=a.getPos().y()-b.getPos().y();
    double s=x_dis*x_dis+y_dis*y_dis;
    return pow(s,0.5);
}

void gameScene::findEnemy()//寻找敌人
{
    for(int i=0;i<towers.size();i++)
        for(int j=0;j<enemies.size();j++)
        {
            double dis=distance(*towers[i],*enemies[j]);
            int num = towers[i]->attack_target.indexOf(enemies[j]);
            if(dis<=towers[i]->getrange()&&num==-1&&enemies[j]->getBlood()>=0)
            {
                towers[i]->attack_target.push_back(enemies[j]);//如果列表中没有敌人，那么把他们列入攻击对象中
            }
            if(num!=-1&&(dis>=towers[i]->getrange()||enemies[j]->getBlood()<=0))
                towers[i]->attack_target.erase(towers[i]->attack_target.begin()+num);//如果超过距离或者死亡则从列表中删除
        }
}

void gameScene::Check()
{
    for(int i=0;i<skills.size();i++)
    {
        if(skills[i]->getDM())
        {
            delete skills[i];
            skills.erase(skills.begin()+i);
            i--;
        }
    }
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i]->isDamage())
        {
            for(int j=0;j<towers.size();j++)
            {
                int index = towers[j]->attack_target.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->attack_target.erase(towers[j]->attack_target.begin() + index);
                }
            }
            sumOFCoins+=enemies[i]->getCoin();
            delete enemies[i];
            enemies.erase(enemies.begin()+i);//如果敌军被杀死后直接消灭
            i--;
        }
    }

}
void gameScene::attackEnemy()//确认造成伤害
{
    int i, j;
    for(i = 0; i < enemies.size(); i++)
    {
        for(j = 0; j < skills.size(); j++){
            if(skills[j]->attWin(enemies[i]->getPos()))
            {
                enemies[i]->attack(skills[j]->getDamage());
                skills[j]->setDamage();
            }
        }

    }

}

void gameScene::CreateSkill()//发动攻击/技能
{

    int i;
    for(i = 0; i < towers.size(); i++){
        if(towers[i]->attack_target.size()!=0&& towers[i]->isFireReady())
        {
            //有仇恨目标、冷却完成、旋转完成，进行开火，同时重置开火属性。
            towers[i]->fireCool();
            Skill* a=new Skill(towers[i]->getID(),towers[i]->attack_target[0]->getPos(),towers[i]);
            skills.push_back(a);
        }
    }
}

void gameScene::WinOfEnemy(){
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i]->win||enemies[i]->getPos().x()<0)
        {
            enemies[i]->win=true;
            lifePower-=enemies[i]->getAttakAbility();
            if(lifePower<=0)
            {
                WarNotEnd=false;
                return;
            }
        }
    }
    if(enemyNum==nowMap->allAttack[1]*nowMap->allAttack[2]&&lifePower>0)
        winOfHuman=true;
    return;
}

void gameScene::Move()
{
    int i;
    for(i = 0; i < enemies.size(); i++)
    {
        int str=enemies[i]->getPath();
        int speed=enemies[i]->getSpeed()+qrand()%5;
        int Obx=enemies[i]->getPos().x();
        int Oby=enemies[i]->getPos().y();
        if(nowMap->paths[str-1].dir==UP)
        {
            if(Oby-speed<nowMap->paths[str-1].ey)
            {
                    enemies[i]->setPath();
                    enemies[i]->setPos(Obx,nowMap->paths[str-1].ey);
            }
            else
                enemies[i]->setPos(Obx,Oby-speed);
        }
        else if(nowMap->paths[str-1].dir==LEFT)
        {
            if(Obx-speed<nowMap->paths[str-1].ex)
            {
                    enemies[i]->setPath();
                    enemies[i]->setPos(nowMap->paths[str-1].ex,Oby);
            }
            else
                enemies[i]->setPos(Obx-speed,Oby);
        }
        else if(nowMap->paths[str-1].dir==DOWN)
        {
            if(Oby+speed>nowMap->paths[str-1].ey)
            {

                    enemies[i]->setPath();
                    enemies[i]->setPos(Obx,nowMap->paths[str-1].ey);
            }
            else
                enemies[i]->setPos(Obx,Oby+speed);
        }
        if(enemies[i]->getPath()==nowMap->nPath+1)
            enemies[i]->win=true;
    }

    for(i = 0; i < skills.size(); i++)
    {
        skills[i]->move();
    }
}

void gameScene::Create()
{
    ifCreate=!ifCreate;
}
