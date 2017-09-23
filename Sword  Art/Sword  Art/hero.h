#pragma once
#include <string>
using namespace std;

class hero
{
public:
	CImage heroR;     //保存英雄的图像
	CImage heroL;
	CImage heroRight;
	CImage heroLeft;
	CImage heroJumpLeft;
	CImage heroLStab;
	CImage heroRStab;
	CImage heroRS;    
	CImage heroLCut;
	CImage heroRCut;
	CImage heroRC;	
	CImage heroLShear;
	CImage heroRShear;
	CImage heroRS2;	
	CImage heroLHack;
	CImage heroRHack;
	CImage heroRH;     

	int keyUp;         //按键抬起
	int x;             //保存英雄的位置
	int x2;
	int y;
	int direct;        //英雄的方向
	bool direct2;		//左右位置信息二
	int frame;         //运动到第几张图片
	int width;          //图片的宽度和高度，用于碰撞判定
	int height;
	string keepname;
	int orignal;
	hero::hero();
	hero::~hero();
};