#include "XAnimateWidget-Roate.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QTransform>
#include <QTimeLine>

#include <QPushButton>
#include <QLabel>
#include <XSVGLabel.h>
#include <QTextEdit>
#include <QFrame>
#include <QCheckBox>
#include <QJsonObject>
#include <QString>

CXAnimateWidgetRoate::CXAnimateWidgetRoate(QWidget *parent,QJsonObject roateIni) : QWidget(parent),
    m_JsonIni(roateIni),m_GrapScene(nullptr),m_pTimeLine(nullptr),m_GraphView(nullptr),m_roateNum(0)
{ 
    m_GraphView = new QGraphicsView(this);
    m_GrapScene = new QGraphicsScene(this);
    m_GraphView->setAttribute(Qt::WA_TranslucentBackground);
    m_GraphView->setWindowFlags(Qt::FramelessWindowHint);
    m_GraphView->setStyleSheet("background:transparent;padding:0px;border:0px");
    m_GraphView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_GraphView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pTimeLine = new QTimeLine(1000, this);
    m_pTimeLine->setLoopCount(0);
    m_pTimeLine->setCurveShape(QTimeLine::LinearCurve);
    connect(m_pTimeLine, &QTimeLine::frameChanged, this, &CXAnimateWidgetRoate::onFrameChanged);

    m_GraphView->setScene(m_GrapScene);
    setSpeed(20);
    start();
}

CXAnimateWidgetRoate::~CXAnimateWidgetRoate()
{

}

void CXAnimateWidgetRoate::paintEvent(QPaintEvent *event)
{
    AddGrapWidgetType<QTextEdit>();
    AddGrapWidgetType<QLabel>();
    AddGrapWidgetType<QPushButton>();
    AddGrapWidgetType<QCheckBox>();
}

void CXAnimateWidgetRoate::start()
{
    m_pTimeLine->start();
}

void CXAnimateWidgetRoate::stop()
{
    m_pTimeLine->stop();
}

void CXAnimateWidgetRoate::setSpeed(const int speed)
{
    m_pTimeLine->setFrameRange(0, speed);
}

void CXAnimateWidgetRoate::setAngleRange(int beginAngle, int endAngle)
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

void CXAnimateWidgetRoate::setRoateIni(QJsonObject roateIni)
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

void CXAnimateWidgetRoate::resizeEvent(QResizeEvent *event)
{
    m_GraphView->resize(this->size());
}

void CXAnimateWidgetRoate::onFrameChanged()
{
    m_roateNum++;
    foreach(auto child, m_listGrapWidget){
        child->setTransform(getTransform(child));
    }
    m_GrapScene->update();
    m_GraphView->update();
}

QPointF CXAnimateWidgetRoate::StringToPoint(QString point)
{
    QStringList listpoint=point.split(",");
    if(listpoint.length()==2)
        return QPointF(listpoint[0].toInt(),listpoint[1].toInt());
    return QPointF();
}

SRoateRange CXAnimateWidgetRoate::StringToRange(QString range)
{
    QStringList listpoint=range.split(",");
    if(listpoint.length()==2)
        return SRoateRange(listpoint[0].toInt(),listpoint[1].toInt());
    return SRoateRange();
}

int CXAnimateWidgetRoate::computeAngle(int range, SRoateRange roateRange)
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
    if(m_roateNum<roateIni.maxFrame||roateIni.maxFrame==0)
    roateIni.nowFrame=m_roateNum;
    if(!roateIni.pos.isNull())
        centerPos=roateIni.pos;
    transform=transform.translate( centerPos.x(),centerPos.y()).rotate(getAngle(roateIni.nowFrame,roateIni),axis).translate(-centerPos.x(),-centerPos.y());
    }
}

template<typename WidgetType>
void CXAnimateWidgetRoate::AddGrapWidgetType()
{
    foreach(auto child, this->findChildren<WidgetType*>()){
        child->setParent(nullptr);
        child->setAttribute(Qt::WA_TranslucentBackground);
        QGraphicsProxyWidget *gw = m_GrapScene->addWidget(child);
        m_listGrapWidget.append(gw);
    }
}
