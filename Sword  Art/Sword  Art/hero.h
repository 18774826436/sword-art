#pragma once
#include <string>
using namespace std;

class hero
{
public:
	CImage heroR;     //����Ӣ�۵�ͼ��
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

	int keyUp;         //����̧��
	int x;             //����Ӣ�۵�λ��
	int x2;
	int y;
	int direct;        //Ӣ�۵ķ���
	bool direct2;		//����λ����Ϣ��
	int frame;         //�˶����ڼ���ͼƬ
	int width;          //ͼƬ�Ŀ�Ⱥ͸߶ȣ�������ײ�ж�
	int height;
	string keepname;
	int orignal;
	hero::hero();
	hero::~hero();
};