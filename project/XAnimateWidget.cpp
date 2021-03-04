#include "XAnimateWidget.h"
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

CXAnimateWidget::CXAnimateWidget(QWidget *parent,QJsonObject JsonIni) : QWidget(parent),
    m_JsonIni(JsonIni),m_GrapScene(nullptr),m_pTimeLine(nullptr),m_GraphView(nullptr),m_frameNum(0)
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
    connect(m_pTimeLine, &QTimeLine::frameChanged, this, &CXAnimateWidget::onFrameChanged);

    m_GraphView->setScene(m_GrapScene);
    setSpeed(1000);
    start();
}

CXAnimateWidget::~CXAnimateWidget()
{

}

void CXAnimateWidget::paintEvent(QPaintEvent *event)
{
    AddGrapWidgetType<QTextEdit>();
    AddGrapWidgetType<QLabel>();
    AddGrapWidgetType<QPushButton>();
    AddGrapWidgetType<QCheckBox>();
}

void CXAnimateWidget::start()
{
    m_pTimeLine->start();
}

void CXAnimateWidget::stop()
{
    m_pTimeLine->stop();
}

void CXAnimateWidget::setSpeed(const int speed)
{
    m_pTimeLine->setFrameRange(0, speed);
}

void CXAnimateWidget::setJsonIni(QJsonObject jsonIni)
{
    m_JsonIni.swap(jsonIni);
}

QTransform CXAnimateWidget::getTransform(QGraphicsProxyWidget *grapWidget)
{
    QTransform transform;
    if(!grapWidget)
        return transform;
    return transform;
}

void CXAnimateWidget::resizeEvent(QResizeEvent *event)
{
    m_GraphView->resize(this->size());
}

void CXAnimateWidget::onFrameChanged()
{
    m_frameNum++;
    foreach(auto child, m_listGrapWidget){
        child->setTransform(getTransform(child));
    }
    m_GrapScene->update();
    m_GraphView->update();
}

QPointF CXAnimateWidget::StringToPoint(QString point)
{
    QStringList listpoint=point.split(",");
    if(listpoint.length()==2)
        return QPointF(listpoint[0].toInt(),listpoint[1].toInt());
    return QPointF();
}

SActiveRange CXAnimateWidget::StringToRange(QString range)
{
    QStringList listpoint=range.split(",");
    if(listpoint.length()==2)
        return SActiveRange(listpoint[0].toInt(),listpoint[1].toInt());
    return SActiveRange();
}

template<typename WidgetType>
void CXAnimateWidget::AddGrapWidgetType()
{
    foreach(auto child, this->findChildren<WidgetType*>()){
        child->setParent(nullptr);
        child->setAttribute(Qt::WA_TranslucentBackground);
        QGraphicsProxyWidget *gw = m_GrapScene->addWidget(child);
        m_listGrapWidget.append(gw);
    }
}
