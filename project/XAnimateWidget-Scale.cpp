#include "XAnimateWidget-Scale.h"


CXAnimateWidgetScale::CXAnimateWidgetScale(QWidget *parent, QJsonObject roateIni):CXAnimateWidget(parent,roateIni)
{

}

CXAnimateWidgetScale::~CXAnimateWidgetScale()
{

}

void CXAnimateWidgetScale::setJsonIni(QJsonObject jsonIni)
{
    m_JsonIni.swap(jsonIni);
}

QTransform CXAnimateWidgetScale::getTransform(QGraphicsProxyWidget *grapWidget)
{
    QTransform transform;
    if(!grapWidget)
        return transform;

    return transform;
}
