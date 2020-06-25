#include "object.h"

Object::Object(double _x,double _y,double W,double H):Obx(_x),Oby(_y),wid(W),hei(H)
{
    object=new QPixmap;
}

QPointF Object::getPos(){
    QPointF point(Obx,Oby);
    return point;
}

void Object::setPos(double _x,double _y){
    Obx=_x;
    Oby=_y;
}

void Object::setWid(double _w,double _h){
    wid=_w;
    hei=_h;
}

void Object::show(QPainter* painter){
    painter->drawPixmap(Obx-wid/2,Oby-hei/2,wid,hei,*object);
}
