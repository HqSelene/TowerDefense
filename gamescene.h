#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "enemy.h"
#include "weapon.h"
#include "map.h"
#include "object.h"
#include "QMouseEvent"
#include "skill.h"

class gameScene:public Object
{
public:
    static int st;
    gameScene();
    void setScene(int n);
    void show(QPainter* painter);

    void SingleClick(QMouseEvent* e);//处理鼠标点击的
     void setTower(QKeyEvent*e);
     void deleteTower();

    void findEnemy();//寻找合适的敌军
    void attackEnemy();//发动攻击

    void WinOfEnemy();//删除到达终点的敌人/或者计算是否成功
    void CreateEnemy();//敌人生成器
    int showWeapon(int x,int y);//选择武器时所展现的
    void Move();//使子弹、敌人移动
    void Check();//确认删除已经死亡或者无效的技能
    void CreateSkill();//发动攻击

    bool ifWin(){return winOfHuman;}
    bool isWarEnd(){return WarNotEnd;}
    int frequency;//控制不同场景下敌人生成的频率


private:
    QVector<Weapon*> towers;//防御塔列表（已激活）
    QVector<enemy*> enemies;//敌人容器
    QVector<Skill*> skills;
    QVector<QPointF*> processTower;

    QPixmap* Coin;
    QPixmap* life;
    int enemyNum,attackNum;
    int sumOFCoins;//金币
    int lifePower;//生命力
    double distance(Object a,Object b);
    Map* nowMap;

    bool WarNotEnd;
    bool winOfHuman;
    bool ifCreate;//判断是否可以制造敌人了

public slots:
    void Create();
};

#endif // GAMESCENE_H
