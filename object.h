#ifndef OBJECT_H
#define OBJECT_H
#include<QPixmap>
#include<QPainter>

class Object
{
public:
    Object(double _x=0,double _y=0,double W=100,double H=100);
    virtual void show(QPainter* painter);//画出这个对象
    virtual ~Object(){}
    QPointF getPos();
    void setPos(double _x,double _y);
    void setWid(double _w,double _h);
    int getID() const {return ID;}
    void setID(int id){ID=id;}

private:
    int ID;
protected:
    QPixmap* object;
    double Obx,Oby;//对象的中心位
    double wid,hei;//对象的高度和宽度
};

#endif // OBJECT_H
