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
        frequency=8000;
        nowMap=new Map(1);
        lifePower=1;
        sumOFCoins=150;
    }
        break;
    case 2:
    {
        frequency=8000;
        nowMap=new Map(2);
        lifePower=8;
        sumOFCoins=200;
    }
        break;
    case 3:
    {
        frequency=8000;
        nowMap=new Map(3);
        lifePower=20;
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
    SkillOfEnemy();
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
    if(!ifCreate)//ifCreate为真时，才产生敌人
        return;
    int a,b;
    diversifyEmy* tmp;
    b=qrand()%3+1;//控制每次生成的敌人的数量，每次生成的敌人个数不超过4
    if(enemyNum+b>nowMap->allAttack[1]*nowMap->allAttack[2])
    {
        b=nowMap->allAttack[1]*nowMap->allAttack[2]-enemyNum;//对于即将产生的敌人数量进行调整，因为敌人总数已经确定，不能超出
    }

    for(int i=0;i<b;i++)
    {
        a=qrand()%nowMap->allAttack[0]+1;//随机生成的敌人种类
        switch (a)
        {
        case 1:
            tmp=new diversifyEmy(1);
            break;
        case 2:
            tmp=new diversifyEmy(2);
            break;
        case 3:
            tmp=new diversifyEmy(3);
            break;
        case 4:
            tmp=new diversifyEmy(4);
            break;
        }
        tmp->setPos(nowMap->getPaths()[0].sx,nowMap->getPaths()[0].sy);//为敌人设置初始位置
        enemies.push_back(tmp);//像容器中添加新产生的敌人的指针
    }
    enemyNum+=b;//地图目前已生成的总敌人数量

    if(enemyNum%nowMap->allAttack[2]==0)//这段语句是用来分析目前进攻波数，每一波敌人数已规定
        attackNum=enemyNum/nowMap->allAttack[2];
    else
        attackNum=enemyNum/nowMap->allAttack[2]+1;

    ifCreate=false;//使ifCreate为假
}


void gameScene::SingleClick(QMouseEvent* e)//处理鼠标点击事件
{
    QPointF* a=new QPointF(e->x(),e->y());
    processTower.push_back(a);//在容器中收集每一次鼠标事件点的位置，并且最后一次鼠标事件的点在容器末

}

void gameScene::setTower(QKeyEvent *e)//键盘事件
{
    if(processTower.size()==0)//已发生鼠标事件后才能进行后续处理，否则无效
        return;
    int p=processTower.size()-1;//f为一状态量，p是processTower容器末尾元素的位置

    for(int i=0;i<towers.size();i++)
    {
        if(distance(Object(processTower.at(p)->x(),processTower.at(p)->y()),*towers[i])<=TILESET/2)
        {
            if(e->key()==Qt::Key_S)//如果该位置已经有了塔并且按了升级按键S，则询问是否要进行升级
            {
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
            }
            processTower.erase(processTower.begin()+p);//在找到相应塔后删除点
            return;
        }
    }

    int num=0;
    if(e->key()==Qt::Key_1)//键1表示创建1号塔
    {
        num=1;
    }
    else if(e->key()==Qt::Key_2)//键2表示创建2号塔
    {
        num=2;
    }
    if(num==0)
        return;

    Weapon* tmp=new Weapon(num,processTower.at(p)->x(),processTower.at(p)->y());
    if(sumOFCoins<tmp->getMoney(0)){
        //金币不足，无法创建塔
        QMessageBox::warning(NULL, "warning", "RUN OUT OF MONEY!");
        processTower.erase(processTower.begin()+p);//删除点
        return;
    }
    towers.push_back(tmp);//在容器中加入新建立的塔
    sumOFCoins-=tmp->getMoney(0);//扣除一定金币
    processTower.erase(processTower.begin()+p);//删除点
}

void gameScene::deleteTower()//玩家删除塔操作
{
    if(processTower.size()==0)//如果没有发生过鼠标事件，则返回
        return;
    int p=processTower.size()-1;//找到最近一次鼠标事件点的位置
    for(int i=0;i<towers.size();i++)
    {
        if(distance(Object(processTower.at(p)->x(),processTower.at(p)->y()),*towers[i])<=TILESET/2)//判断这个点是否有塔
        {
            //有塔则进行提示，是否删除
            QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Delete", "Do you want to delete this weapon?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb==QMessageBox::Yes)
            {
                //确定删除后，能够返回一定金币，并且将该塔状态设置为已毁灭
                sumOFCoins+=towers[i]->getMoney(towers[i]->getlevel())/2;
                towers[i]->setDamage();
            }
        }
    }
    processTower.erase(processTower.begin()+p);//删除点
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
    for(int i=0;i<skills.size();i++)//子弹毁灭则删除子弹
    {
        if(skills[i]->getDM())
        {
            delete skills[i];
            skills.erase(skills.begin()+i);
            i--;
        }
    }
    for(int i=0;i<enemies.size();i++)//敌人毁灭或者敌人到达终点则删除敌人，
    {
        if(enemies[i]->isDamage()||enemies[i]->win==true)
        {
            for(int j=0;j<towers.size();j++)
            {
                int index = towers[j]->attack_target.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->attack_target.erase(towers[j]->attack_target.begin() + index);
                }
            }
            if(!enemies[i]->win)
                sumOFCoins+=enemies[i]->getCoin();//如果敌军是被杀死的，则可以获得金币
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
            i--;
        }

    }
    for(int i=0;i<towers.size();i++)//塔毁灭则删除塔
    {
        if(towers[i]->getDamage())
        {
            delete towers[i];
            towers.erase(towers.begin()+i);
        }
    }
}
void gameScene::attackEnemy()//确认造成伤害
{
    int i, j;
    for(i = 0; i < enemies.size(); i++)
    {
        for(j = 0; j < skills.size(); j++)
        {
            if(skills[j]->attWin(enemies[i]->getPos()))//判断子弹是否打中该敌人
            {
                enemies[i]->attack(skills[j]->getDamage());//如果打中则设置敌人属性为已毁灭
                skills[j]->setDamage();
            }
        }
    }
}

void gameScene::CreateSkill()//发动攻击
{
    int i;
    for(i = 0; i < towers.size(); i++){
        if(towers[i]->attack_target.size()!=0&& towers[i]->isFireReady())
        {
            //塔如果有仇恨目标、并且武器已经冷却完成后，发动攻击，同时重置开火属性。
            towers[i]->fireCool();
            Skill* a=new Skill(towers[i]->getID(),towers[i]->attack_target[0]->getPos(),towers[i]);
            skills.push_back(a);
        }
    }
}

void gameScene::SkillOfEnemy()
{
    for(int i=0;i<enemies.size();i++)
    {
        switch (enemies[i]->getID())
        {
        case 3:
            enemies[i]->receiveWpn(towers);//3号敌人需要接受所生成的塔，以寻找攻击目标
        case 4:
            enemies[i]->receiveEmy(enemies);//4号敌人需要接收目前所有的敌人，以找到技能发动目标
        }
    }
}


void gameScene::WinOfEnemy(){
    if(enemies.size()==0&&enemyNum>=nowMap->allAttack[1]*nowMap->allAttack[2])
        WarNotEnd=false;//检查敌人是否全部生成完成
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i]->win||enemies[i]->getPos().x()<0)
        {
            enemies[i]->win=true;
            lifePower-=enemies[i]->getAttakAbility();//如果敌人成功到达终点，则本方生命力减少
            if(lifePower<=0)//若本方生命力<0，怎敌军胜利
            {
                winOfHuman=false;
                WarNotEnd=false;
                return;
            }
        }
    }
    if(lifePower>0&&!WarNotEnd)//如果敌人全部生成后，且enemies容器中没有元素后我方胜利
        winOfHuman=true;
    return;
}

void gameScene::Move()
{
    int i;
    for(i = 0; i < enemies.size(); i++)
    {
        int str=enemies[i]->getPath();//敌人目前所在道路
        int speed=enemies[i]->getSpeed()+qrand()%5;//敌人在原本速度的基础上，每次都会随机5步以内的浮动
        //取得敌人目前所在位置
        int Obx=enemies[i]->getPos().x();
        int Oby=enemies[i]->getPos().y();

        QVector<strPath> paths=nowMap->getPaths();
        //根据该路的方向，设定敌人移动后的位置
        if(paths[str-1].dir==UP)
        {
            if(Oby-speed<paths[str-1].ey)
            {
                    enemies[i]->setPath();
                    enemies[i]->setPos(Obx,paths[str-1].ey);
            }
            else
                enemies[i]->setPos(Obx,Oby-speed);
        }
        else if(paths[str-1].dir==LEFT)
        {
            if(Obx-speed<paths[str-1].ex)
            {
                    enemies[i]->setPath();
                    enemies[i]->setPos(paths[str-1].ex,Oby);
            }
            else
                enemies[i]->setPos(Obx-speed,Oby);
        }
        else if(paths[str-1].dir==DOWN)
        {
            if(Oby+speed>paths[str-1].ey)
            {

                    enemies[i]->setPath();
                    enemies[i]->setPos(Obx,paths[str-1].ey);
            }
            else
                enemies[i]->setPos(Obx,Oby+speed);
        }

        //如果敌人已经走完了所有的路，则该敌人成功到达我方大本营，其win属性为真
        if(enemies[i]->getPath()==nowMap->getNumPath()+1)
            enemies[i]->win=true;
    }
    for(i = 0; i < skills.size(); i++)
    {
        skills[i]->move();//在此中调用子弹的移动
    }
}


void gameScene::Create()
{
    ifCreate=!ifCreate;
}
