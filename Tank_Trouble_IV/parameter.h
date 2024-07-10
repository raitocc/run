#ifndef PARAMETER_H
#define PARAMETER_H

//TankTurret类在tank.h中
//BulletSupply类在bullet.h中

//给item加的data的key
#define ITEM_TYPE 0
#define GRID_TYPE 1
#define BULLET_TYPE 1
#define BULLET_AMOUNT 2

//item类型
#define PLAYER_TANK 0
#define ENEMY_TANK 1
#define GRID 2
#define BULLET 3
#define BULLET_SUPLLY 4

//格子类型
#define WALL 0
#define BOX 1
#define AIR 2


#define GRIDSIZE 60//格子宽度
#define TANK_WIDTH 23//坦克宽度
#define TANK_LENGTH 30//坦克长度

#define MAX_BULLET_TYPE 16//最大子弹种类数
#define MAX_PROP_TYPE 16//最大道具种类数

//游戏状态栏高度
#define STATEBAR_HEIGHT 70



//移动状态
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#endif // PARAMETER_H
