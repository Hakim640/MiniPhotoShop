/*
*	Pixmap32b�� 32λλͼ
*	֧��RGB��YUV��ɫ��ʽ�Լ��ҽס���ֵͼ���ʽ
*/
#ifndef PIXMAP32B_H
#define PIXMAP32B_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <QImage>
#include "DataStructure.h"
typedef unsigned char UNUM8;	//8λ�޷�����
typedef unsigned short UNUM16;	//16λ�޷�����
typedef unsigned int UNUM32;	//32λ�޷�����
typedef signed char SNUM8;		//8λ�з�����
typedef signed short SNUM16;	//16λ�з�����
typedef signed int SNUM32;		//32λ�з�����

enum { FMT_NULL, FMT_RGB, FMT_YUV,FMT_GREY,FMT_BIN};	//��ʾPixmap32b״̬ FMT_NULLΪ������ FMT_RGBΪRGBA��ʽ���� FMT_YUVΪYUV��ʽ����(YUV�ֱ��Ӧr,b,g����) FMT_BINΪ��ֵͼ��RGBA��ʽ�洢��

typedef struct {
	UNUM8 r, g, b, a,empty;
}Pixel32b;

class Pixmap32b:public BaseShape
{
	unsigned int height, width, format;	//heightΪͼ��߶� widthΪͼ���� formatΪ״̬
	UNUM8 *r, *g, *b, *a;	//r��g��b��aΪ4��ͨ�������� ˳��Ϊ�����µ����ϣ����к���
public:
    Pixmap32b(const char* fileName = NULL) : BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL) { LoadBmpFile(fileName); }	//��ͼƬ�ļ�����
	Pixmap32b(unsigned int width, unsigned int height,unsigned char value=0);	//�½�height*width��С����ʼ��ɫΪ��ɫ��ͼƬ��RGB��ʽ
    Pixmap32b(const Pixmap32b &pixmap) :BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL) { Load(pixmap); }//�������캯��
    Pixmap32b(const QImage *image):BaseShape(0, 0, SHAPE::PIXMAP, string("Pixmap"), 1.0, 1.0, 0),width(0), height(0), r(NULL), g(NULL), b(NULL), a(NULL), format(FMT_NULL){
        if(image->format()!=QImage::Format_ARGB32){
            QImage *newimage=&(image->convertToFormat(QImage::Format_ARGB32,image->colorTable()));
            LoadQImage(newimage);
            delete newimage;
        }else{
            LoadQImage(image);
        }
    }

    ~Pixmap32b() { FreePixmap32b(); }

    int LoadQImage(const QImage *image);
    QImage getQImage();

	int LoadBmpFile(const char * fileName);	//���Դ�ͼƬ�ļ���������
	int Load(const Pixmap32b &pixmap);	//�������캯��
	int SaveAsBMP24b(const char * fileName) const;	//�洢Ϊ24λBMPͼƬ
	int SaveAsGreyBMP8b(const char * fileName) const;	//�洢Ϊ8λ�Ҷ�ͼƬ
	void FreePixmap32b();	//�������

	int ConvertFormat(unsigned int newFormat, int thre=-1);	//ת����ʽ
	int ConvertToYUV();	//ת��ΪYUV��ɫ��ʽ
	int ConvertToRGB();	//ת��ΪRGB��ɫ��ʽ
	int ConvertToGrey();	//��YUV�е�Yͨ�����RGB��ת��Ϊ�ҽ�ͼ��
	unsigned char OtsuGetThre();	//��ô����ֵ
	int ConvertToBin(int thre=-1);	//��ֵ������thre����0~255֮�䣬���Ƚ��д������ֵ����
	void ChangeLuma(int del);	//�ı�YUVͨ���е�Yֵ�����ָ�ԭ��ʽ
	int InverseColor();	//��ɫ
	int LogOperation();	//��������
	int HistoEqualizing();	//ֱ��ͼ����
	Pixel32b NearestInterpolation(double x,double y) const;	//���ڽ���ֵ
	Pixel32b BilinearInterpolation(double x,double y) const;	//˫���Բ�ֵ
	static double Gaussian(double x,double r);//�����˹�ֲ� 
	
	static int AffineTrans(const Pixmap32b *src,Pixmap32b *dst,double *matrix, int interpolMethod=0,UNUM8 backR=255,UNUM8 backG=255,UNUM8 backB=255);	//���ݾ�����з���任  ����(x,y,1)ת�� matrix 3*3����˳�� (1,1) (1,2) (1,3) (2,1) (2,2) (2,3) (3,1) (3,2) (3,3)
	Pixmap32b *Translation(double x,double y,int autoExpand=1,int interpolMethod=0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//ƽ��
	Pixmap32b *Rotation(double angle, int autoExpand = 1,int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//��ת
	Pixmap32b *Mirror(int x,int y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//����
	Pixmap32b *Scale(double x, double y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//����
	Pixmap32b *Shear(double x, double y, int autoExpand = 1, int interpolMethod = 0, UNUM8 backR = 255, UNUM8 backG = 255, UNUM8 backB = 255);	//б��

	Pixmap32b *Dilation(const Pixmap32b *stElement,unsigned int anchorX,unsigned int anchorY,unsigned int inverse=0) const;	//����
	Pixmap32b *Erosion(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse=0) const;	//��ʴ
	Pixmap32b *Opening(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse = 0) const;	//������
	Pixmap32b *Closing(const Pixmap32b * stElement, unsigned int anchorX, unsigned int anchorY, unsigned int inverse = 0) const;	//������

	Pixmap32b *AddBorder(unsigned int borderWidth,int mode=0) const;	//�����Ե��չ
	Pixmap32b *Convolution(double * filter, unsigned int filterSize, int normalization=1,double **outR=NULL,double **outG=NULL,double **outB=NULL) const;	//���
	Pixmap32b *LaplacianEnhance(double * filter=NULL, unsigned int filterSize=0) const;	//������˹ͼ����ǿ
	Pixmap32b *BilateralFiltering(int filterSize=-1,double intenPara=-1,double spacePara=-1) const;//˫���˲� 

	unsigned int getWidth() const { return width; }	//����ͼƬ���
	unsigned int getHeight() const { return height; }	//����ͼƬ�߶�

	const unsigned char *getRHead() const { return r; }	//����r����
	const unsigned char *getGHead() const { return g; }	//����g����
	const unsigned char *getBHead() const { return b; }	//����b����
	const unsigned char *getAHead() const { return a; }	//����a����

	unsigned char *getRHead() { return r; }	//�ǳ����� ����r����
	unsigned char *getGHead() { return g; }	//�ǳ����� ����g����
	unsigned char *getBHead() { return b; }	//�ǳ����� ����b����
	unsigned char *getAHead() { return a; }	//�ǳ����� ����a����

	unsigned int getFormat() const { return format; }	//���ظ�ʽ

	const unsigned char *getR(unsigned int x, unsigned int y) const { if (x < width&&y < height) return r + y*width + x; return NULL; }//����(x,y)���괦��rֵָ��
	const unsigned char *getG(unsigned int x, unsigned int y) const { if (x < width&&y < height)return g + y*width + x; return NULL; } //����(x,y)���괦��gֵָ��
	const unsigned char *getB(unsigned int x, unsigned int y) const { if (x < width&&y < height) return b + y*width + x; return NULL; } //����(x,y)���괦��bֵָ��
	const unsigned char *getA(unsigned int x, unsigned int y) const { if (x < width&&y < height) return a + y*width + x; return NULL; } //����(x,y)���괦��aֵָ��
	Pixel32b getPixel(unsigned int x,unsigned int y) const;	//���(x,y)�������ص���ɫ
	
	unsigned char *getR(unsigned int x, unsigned int y) { if (x < width&&y < height) return r + y*width + x; return NULL; } //�ǳ����� ����(x,y)���괦��rֵָ��
	unsigned char *getG(unsigned int x, unsigned int y) { if (x < width&&y < height) return g + y*width + x; return NULL; }//�ǳ����� ����(x,y)���괦��gֵָ��
	unsigned char *getB(unsigned int x, unsigned int y) { if (x < width&&y < height) return b + y*width + x; return NULL; }//�ǳ����� ����(x,y)���괦��bֵָ��
	unsigned char *getA(unsigned int x, unsigned int y) { if (x < width&&y < height) return a + y*width + x; return NULL; }//�ǳ����� ����(x,y)���괦��aֵָ��

};

#endif
