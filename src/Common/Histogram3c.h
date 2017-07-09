/*
*	Histogram3c�� 3ͨ��ֱ��ͼ
*/
#ifndef HISTOGRAM3C_H
#define HISTOGRAM3C_H

#include "Pixmap32b.h"

enum {SELECT_R=1,SELECT_G=2,SELECT_B=4,SELECT_GREY=8};	//�����Ҫ������ͨ��

class Histogram3c
{
	unsigned int *hgR, *hgG, *hgB;	//3ͨ����ɫ����
public:
	Histogram3c();
	Histogram3c(Pixmap32b &pixmap,unsigned char select=SELECT_R|SELECT_G|SELECT_B);
	~Histogram3c() { FreeHistogram3c(); }
	void FreeHistogram3c();
	void LoadPixmap(Pixmap32b &pixmap, unsigned char select = SELECT_R | SELECT_G | SELECT_B);	//��Pixmap32b�����ֱ��ͼ
	unsigned int* CalcHistogram(unsigned int total,const unsigned char *color);
	unsigned int getRCount(unsigned char r) const;
	unsigned int getGCount(unsigned char g) const;
	unsigned int getBCount(unsigned char b) const;
	unsigned int *getRHead() { return hgR; }
	unsigned int *getGHead() { return hgG; }
	unsigned int *getBHead() { return hgB; }
};

#endif
