#include "XAnimateWidget-Demo.h"


CXAnimateWidgetDemo::CXAnimateWidgetDemo(QWidget *parent, QJsonObject roateIni):CXAnimateWidget(parent,roateIni)
{

}

CXAnimateWidgetDemo::~CXAnimateWidgetDemo()
{

}

void CXAnimateWidgetDemo::setRoateIni(QJsonObject roateIni)
{
    m_JsonIni.swap(roateIni);
}

QTransform CXAnimateWidgetDemo::getTransform(QGraphicsProxyWidget *grapWidget)
{
    QTransform transform;
    if(!grapWidget)
        return transform;
    return transform;
}
