#include "map.h"
#include "data.h"
#include "weapon.h"

Map::Map(int num):Object(MAPWIDE/2,MAPHEIGHT/2,MAPWIDE,MAPHEIGHT)
{
    object=new QPixmap;
    switch(num){
    case 1:
    {
        object->load("://picture/map/map1.png");
        setPath(1);//n
        allAttack=new int[3]{2,10,10};

    }
        break;
    case 2:
    {
        object->load("");
        setPath(2);
        allAttack=new int[3]{3,15,12};
    }
        break;
    case 3:
    {
        object->load("");
    }
        break;
    case 4:
    {
        object->load("");
    }
        break;
    }
}

void Map::setPath(int n)
{
    switch (n)
    {
    case 1:
    {
        nPath=1;
        paths.push_back(strPath(MAPWIDE,MAPHEIGHT/2,0,MAPHEIGHT/2,LEFT));
    }
        break;
    case 2:
    {
        nPath=5;
        paths.push_back(strPath(MAPWIDE,MAPHEIGHT/3,MAPWIDE*2/3,MAPHEIGHT/3,LEFT));
        paths.push_back(strPath(MAPWIDE*2/3,MAPHEIGHT/3,MAPWIDE*2/3,MAPHEIGHT*2/3,DOWN));
        paths.push_back(strPath(MAPWIDE*2/3,MAPHEIGHT*2/3,MAPWIDE/3,MAPHEIGHT*2/3,LEFT));
        paths.push_back(strPath(MAPWIDE/3,MAPHEIGHT*2/3,MAPWIDE/3,MAPHEIGHT/3,UP));
        paths.push_back(strPath(MAPWIDE/3,MAPHEIGHT/3,0,MAPHEIGHT/3,LEFT));
    }
        break;
    }
}

