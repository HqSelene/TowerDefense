#ifndef MAP_H
#define MAP_H
#include"object.h"
#include "enemy.h"

#include<QProgressBar>
#include<QVector>
#include<QPainter>
#include<QGraphicsSceneMouseEvent>
#include<QMouseEvent>

class strPath{
public:
    double sx,sy,ex,ey;
    int dir;//记录该路线的方向
    strPath(double a,double b,double c,double d,int e):sx(a),sy(b),ex(c),ey(d),dir(e){};
};

class Map:public Object
{
public:
    Map(int num=0);
    void setPath(int n);
    int* allAttack;//分别代表敌人种类数量，进攻波数目，每一波的数量
    QVector<strPath> getPaths(){return paths;}
    int getNumPath(){return nPath;}

private:
    QVector<strPath> paths;//路线
    int nPath;//路有几条呢
    int startMoney;

};

#endif // MAP_H
