#include "XAnimateWidget-Roate.h"
#include <QDebug>

CXAnimateWidgetRoate::CXAnimateWidgetRoate(QWidget *parent,QJsonObject roateIni) : CXAnimateWidget(parent,roateIni)
{ 
}

CXAnimateWidgetRoate::~CXAnimateWidgetRoate()
{

}

QTransform CXAnimateWidgetRoate::getTransform(QGraphicsProxyWidget *grapWidget)
{
    QTransform transform;
    if(!grapWidget)
        return transform;
    int centerX = grapWidget->boundingRect().width()/2;
    int centerY = grapWidget->boundingRect().height()/2;
    SetTransform(transform, m_RoateIni.X, QPointF(centerX,centerY),Qt::XAxis);
    SetTransform(transform, m_RoateIni.Y, QPointF(centerX,centerY),Qt::YAxis);
    SetTransform(transform, m_RoateIni.Z, QPointF(centerX,centerY),Qt::ZAxis);
    return transform;
}

int CXAnimateWidgetRoate::getAngle(int nowFrame, ST_RoateIni roateIni)
{
    int range=0,maxRange;
    maxRange=roateIni.range.max;
    if(qAbs(roateIni.range.length())==360){
        range=-nowFrame*roateIni.angle%360;
    }
    else
        range=-nowFrame*roateIni.angle%(2*roateIni.range.length());

    if(roateIni.range.isEmply())
        return range;

    range=computeAngle(range,roateIni.range);
    return range;
}

void CXAnimateWidgetRoate::setJsonIni(QJsonObject roateIni)
{
    m_JsonIni.swap(roateIni);
    int angle_X=m_JsonIni["angle_x"].toInt();
    int angle_Y=m_JsonIni["angle_y"].toInt();
    int angle_Z=m_JsonIni["angle_z"].toInt();
    int speed=m_JsonIni["speed"].toInt();
    if(speed<=0)
        speed=0;
    else if(speed>1000)
        speed=1000;

    m_RoateIni.X.pos=StringToPoint(m_JsonIni["pos_x"].toString());
    m_RoateIni.Y.pos=StringToPoint(m_JsonIni["pos_y"].toString());
    m_RoateIni.Z.pos=StringToPoint(m_JsonIni["pos_z"].toString());
    /*每帧转动角度*/
    m_RoateIni.X.angle=angle_X;
    m_RoateIni.Y.angle=angle_Y;
    m_RoateIni.Z.angle=angle_Z;
    /*转动角度范围*/
    m_RoateIni.X.range=StringToRange(m_JsonIni["range_x"].toString());
    m_RoateIni.Y.range=StringToRange(m_JsonIni["range_y"].toString());
    m_RoateIni.Z.range=StringToRange(m_JsonIni["range_z"].toString());
    /*最大转动次数*/
    m_RoateIni.X.maxFrame=m_JsonIni["maxframe_x"].toInt();
    m_RoateIni.Y.maxFrame=m_JsonIni["maxframe_y"].toInt();
    m_RoateIni.Z.maxFrame=m_JsonIni["maxframe_z"].toInt();
    /*每秒转动帧数*/
    m_RoateIni.speed=speed;
    setSpeed(m_RoateIni.speed);
}

void CXAnimateWidgetRoate::setRoateIni(QJsonObject roateIni)
{
    setJsonIni(roateIni);
}

int CXAnimateWidgetRoate::computeAngle(int range, SActiveRange roateRange)
{
    if(range>roateRange.max){
        range=2*roateRange.max-range;
    }
    if(range<roateRange.min){
        range=2*roateRange.min-range;
    }
    if(range>=roateRange.min&&range<=roateRange.max)
        return range;
    else
        return computeAngle(range,roateRange);
}

void CXAnimateWidgetRoate::SetTransform(QTransform &transform, CXAnimateWidgetRoate::ST_RoateIni &roateIni, QPointF centerPos,Qt::Axis axis)
{
    if(roateIni.angle!=0){
    if(m_frameNum<roateIni.maxFrame||roateIni.maxFrame==0)
    roateIni.nowFrame=m_frameNum;
    if(!roateIni.pos.isNull())
        centerPos=roateIni.pos;
    transform=transform.translate( centerPos.x(),centerPos.y()).rotate(getAngle(roateIni.nowFrame,roateIni),axis).translate(-centerPos.x(),-centerPos.y());
    }
}

