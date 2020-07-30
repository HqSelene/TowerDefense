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
        allAttack=new int[3]{2,1,1};

    }
        break;
    case 2:
    {
        object->load("://picture/map/map2.png");
        setPath(2);
        allAttack=new int[3]{3,15,10};
    }
        break;
    case 3:
    {
        object->load("://picture/map/map3.png");
        setPath(3);
        allAttack=new int[3]{4,18,12};
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
    case 3:
    {
        nPath=7;
        paths.push_back(strPath(MAPWIDE,MAPHEIGHT/2,MAPWIDE*3/4,MAPHEIGHT/2,LEFT));
        paths.push_back(strPath(MAPWIDE*3/4,MAPHEIGHT/2,MAPWIDE*3/4,MAPHEIGHT*2/3,DOWN));
        paths.push_back(strPath(MAPWIDE*3/4,MAPHEIGHT*2/3,MAPWIDE/2,MAPHEIGHT*2/3,LEFT));
        paths.push_back(strPath(MAPWIDE/2,MAPHEIGHT*2/3,MAPWIDE/2,MAPHEIGHT/3,UP));
        paths.push_back(strPath(MAPWIDE/2,MAPHEIGHT/3,MAPWIDE/4,MAPHEIGHT/3,LEFT));
        paths.push_back(strPath(MAPWIDE/4,MAPHEIGHT/3,MAPWIDE/4,MAPHEIGHT/2,DOWN));
        paths.push_back(strPath(MAPWIDE/4,MAPHEIGHT/2,0,MAPHEIGHT/2,LEFT));
    }
        break;
    }
}
