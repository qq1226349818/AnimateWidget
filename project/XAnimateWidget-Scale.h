#ifndef CXANIMATEWIDGETSCALE_H
#define CXANIMATEWIDGETSCALE_H
#include "XAnimateWidget.h"

class CXAnimateWidgetScale : public CXAnimateWidget
{
    Q_OBJECT
public:
    explicit CXAnimateWidgetScale(QWidget *parent = nullptr,QJsonObject roateIni=QJsonObject());
    ~CXAnimateWidgetScale();
    void setJsonIni(QJsonObject roateIni);
protected:
    QTransform getTransform(QGraphicsProxyWidget* grapWidget);

};

#endif // CXANIMATEWIDGETSCALE_H
