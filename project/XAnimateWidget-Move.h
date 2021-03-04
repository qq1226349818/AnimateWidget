#ifndef CXANIMATEWIDGETMOVE_H
#define CXANIMATEWIDGETMOVE_H


#include "XAnimateWidget.h"

class CXAnimateWidgetMove : public CXAnimateWidget
{
    Q_OBJECT
public:
    /* move:16,20 -16,5;
     * time:3 3 2
     * maxframe:8
    */
    struct ST_MoveIni{
        /*最大移动多少帧*/
        qreal frame;
        /*移动多少帧*/
        qreal frame_now;
        /*X,Y轴移动距离*/
        QPointF move_begin;
        /*X,Y轴移动距离*/
        QPointF move_end;
        /*X,Y轴当前移动距离*/
        QPointF move_now;
        /*移动速度*/
        QPointF move_speed;
    };
    explicit CXAnimateWidgetMove(QWidget *parent = nullptr,QJsonObject roateIni=QJsonObject());
    ~CXAnimateWidgetMove();
    void setJsonIni(QJsonObject jsonIni);
protected:
    QTransform getTransform(QGraphicsProxyWidget* grapWidget);
private:
    QList<ST_MoveIni> m_listMoveIni;
    bool m_back;
    bool m_isLoop=true;
    int m_loopTime=0;
    int m_loopTimeMax=-1;
    int m_maxFrame=0;
    int m_index=0;

    void SetTransform(QTransform &transform, ST_MoveIni &scaleIni);

   ST_MoveIni& getMoveIni();
};

#endif // CXANIMATEWIDGETMOVE_H
