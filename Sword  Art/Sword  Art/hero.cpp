#include "stdafx.h"
//#include "GameMFC.h"

#include "afxdialogex.h"
//#include "signup.h"
#include "hero.h"
#include <windows.h>
#include "mmsystem.h"

//������ĸ�����
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
//�������ﶯ��
#define JUMP 4
#define STAB 5
#define RUN 12
//����̧����
#define DOMNUP 6
#define LEFTUP 7
#define RIGHTUP 8
#define UPUP 9
#define JUMPUP 10
#define STABUP 11

hero::hero()
{
	frame=0;
	direct=-1;
	x=180;    
	x2=180;///*
	orignal = 180;///*
	y=500;//666
	width = 100;
	height = 150;	
	direct2 = true;
}
hero::~hero()
{
}