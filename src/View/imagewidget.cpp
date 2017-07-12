#include "imagewidget.h"
#include <cmath>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image=new QImage;
    //viewPortScale=1.0;
    setCursor(QCursor(Qt::CrossCursor));
}

void ImageWidget::paintEvent(QPaintEvent *event)
{

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    if(image!=NULL&&!image->isNull())
    {
        p.drawImage(QRectF(0,0,realWidth,realHeight),*image,QRectF(0,0,image->width(),image->height()));
    }
    switch(*state)
    {
    case STATE::INIT:break;
    case STATE::DRAW_LINE:
        if(pen!=NULL)
        {
            QPen tmpPen(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()));
            tmpPen.setStyle(static_cast<Qt::PenStyle>(pen->getPenStyle()));
            tmpPen.setWidth(pen->getLineWidth());
            p.setPen(tmpPen);
            p.drawLine(mouseLastX,mouseLastY,mouseX,mouseY);
        }
        break;
    case STATE::DRAW_ELLIPSE:
        if(pen!=NULL&&brush!=NULL)
        {
            QPen tmpPen(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()));
            QBrush tmpBrush(QColor(brush->getBackR(),brush->getBackG(),brush->getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(pen->getPenStyle()));
            tmpPen.setWidth(pen->getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(brush->getBrushStyle()));
            p.setPen(tmpPen);
            p.setBrush(tmpBrush);
            p.drawEllipse(QPoint(mouseLastX,mouseLastY),std::abs(mouseX-mouseLastX),std::abs(mouseY-mouseLastY));
        }
        break;
    case STATE::DRAW_RECT:
        if(pen!=NULL&&brush!=NULL)
        {
            QPen tmpPen(QColor(pen->getForeR(),pen->getForeG(),pen->getForeB()));
            QBrush tmpBrush(QColor(brush->getBackR(),brush->getBackG(),brush->getBackB()));

            tmpPen.setStyle(static_cast<Qt::PenStyle>(pen->getPenStyle()));
            tmpPen.setWidth(pen->getLineWidth());
            tmpBrush.setStyle(static_cast<Qt::BrushStyle>(brush->getBrushStyle()));
            p.setPen(tmpPen);
            p.setBrush(tmpBrush);
            p.drawRect(mouseLastX,mouseLastY,mouseX-mouseLastX,mouseY-mouseLastY);
        }
        break;
    }
}

void ImageWidget::ClearImage()
{
    image=NULL;
    update();
}

void ImageWidget::paintUpdate()
{
    update();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    emit CursorMove(event->localPos().x(),event->localPos().y());
    switch(*state)
    {
    case STATE::DRAW_LINE_INIT:
        *state=STATE::DRAW_LINE;
        emit StateChanged();
        mouseX=mouseLastX=event->localPos().x();
        mouseY=mouseLastY=event->localPos().y();
        break;
    case STATE::DRAW_ELLIPSE_INIT:
        *state=STATE::DRAW_ELLIPSE;
        emit StateChanged();
        mouseX=mouseLastX=event->localPos().x();
        mouseY=mouseLastY=event->localPos().y();
        break;
    case STATE::DRAW_RECT_INIT:
        *state=STATE::DRAW_RECT;
        emit StateChanged();
        mouseX=mouseLastX=event->localPos().x();
        mouseY=mouseLastY=event->localPos().y();
        break;
    case STATE::MOVE_INIT:{
        *state=STATE::MOVE;
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
        qDebug()<<"begin move";
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();
        emit StateChanged();

    }
        break;
    case STATE::SCALE_INIT:{
        *state=STATE::SCALE;
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();
        emit StateChanged();

    }
        break;
    case STATE::ROTATE_INIT:{
        *state=STATE::ROTATE;
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEBEGIN);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();
        emit StateChanged();

    }
        break;
    }
    update();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
     emit CursorMove(-1,-1);
    int centerX,centerY;
    Params para;
    switch(*state)
    {
    case STATE::DRAW_LINE:
        *state=STATE::DRAW_LINE_INIT;
        emit StateChanged();
        //Params para;
        qDebug()<<mouseX<<mouseY<<mouseLastX<<mouseLastY;
        centerX=(mouseLastX+mouseX)/2,centerY=(mouseLastY+mouseY)/2;
        para.setInts({centerX,centerY,mouseLastX-centerX,
                      mouseLastY-centerY,mouseX-centerX,
                      mouseY-centerY});
        addLineCommand->setParams(para);
        addLineCommand->exec();
        qDebug()<<"Finish Draw Line";
        break;
    case STATE::DRAW_ELLIPSE:
        *state=STATE::DRAW_ELLIPSE_INIT;
        emit StateChanged();
        centerX=mouseLastX,centerY=mouseLastY;
        para.setInts({centerX,centerY,std::abs(mouseX-mouseLastX),std::abs(mouseY-mouseLastY)});
        addEllipseCommand->setParams(para);
        addEllipseCommand->exec();
        break;
    case STATE::DRAW_RECT:
        *state=STATE::DRAW_RECT_INIT;
        emit StateChanged();
        centerX=(mouseLastX+mouseX)/2,centerY=(mouseLastY+mouseY)/2;
        para.setInts({centerX,centerY,std::abs(mouseX-mouseLastX),std::abs(mouseY-mouseLastY)});
        addRectCommand->setParams(para);
        addRectCommand->exec();
        break;
    case STATE::MOVE:{
        *state=STATE::MOVE_INIT;
        emit StateChanged();
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEEND);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();}
        break;

    case STATE::SCALE:{
        *state=STATE::SCALE_INIT;
        emit StateChanged();
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEEND);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();}
        break;
    case STATE::ROTATE:{
        *state=STATE::ROTATE_INIT;
        emit StateChanged();
        Params params;
        params.setType(COMMAND::LAYOUT_CHANGEEND);
        layoutTransNotifyCommand->setParams(params);
        layoutTransNotifyCommand->exec();}
        break;
    }
    update();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
     emit CursorMove(event->localPos().x(),event->localPos().y());
    switch(*state)
    {
    case STATE::MOVE:
    {
        Params params;
        params.setType(COMMAND::LAYOUT_MOVE);
        params.setInts({(int)(event->localPos().x()-mouseX),(int)(event->localPos().y()-mouseY)});

        layoutTransCommand->setParams(params);
        layoutTransCommand->exec();
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
    }
        break;

    case STATE::SCALE:
    {
        Params params;
        params.setType(COMMAND::LAYOUT_SCALE);
        params.setDoubles({(double)((event->localPos().x()-mouseX))*SETTINGS::SCALE_STEP+1,(double)((event->localPos().y()-mouseY))*SETTINGS::SCALE_STEP+1});
        layoutTransCommand->setParams(params);
        layoutTransCommand->exec();
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
    }
        break;

    case STATE::ROTATE:
    {
        Params params;
        params.setType(COMMAND::LAYOUT_ROTATE);
        params.setDoubles({(double)((event->localPos().x()-mouseX))*SETTINGS::ROTATE_STEP});
        layoutTransCommand->setParams(params);
        layoutTransCommand->exec();
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
    }
        break;
    default:
        mouseX=event->localPos().x();
        mouseY=event->localPos().y();
        update();

    }
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    realWidth=event->size().width();
    realHeight=event->size().height();
    if(newCanvasCommand!=nullptr)
    {
        Params params;
        params.setInts({realWidth,realHeight});
        newCanvasCommand->setParams(params);
        newCanvasCommand->exec();
    }

}
