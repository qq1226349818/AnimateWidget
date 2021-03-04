#ifndef CXANIMATEWIDGETDEMO_H
#define CXANIMATEWIDGETDEMO_H

#include "XAnimateWidget.h"

class CXAnimateWidgetDemo : public CXAnimateWidget
{
    Q_OBJECT
public:
    explicit CXAnimateWidgetDemo(QWidget *parent = nullptr,QJsonObject roateIni=QJsonObject());
    ~CXAnimateWidgetDemo();
    void setRoateIni(QJsonObject roateIni);
protected:
    QTransform getTransform(QGraphicsProxyWidget* grapWidget);
};

#endif // CXANIMATEWIDGETDEMO_H
