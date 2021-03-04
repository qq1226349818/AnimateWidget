#ifndef CXANIMATEWIDGETROATE_H
#define CXANIMATEWIDGETROATE_H

#include "XAnimateWidget.h"
#include <QWidget>
#include <QJsonObject>

class CXAnimateWidgetRoate : public CXAnimateWidget
{
    Q_OBJECT
public:
    explicit CXAnimateWidgetRoate(QWidget *parent = nullptr,QJsonObject roateIni=QJsonObject());
    ~CXAnimateWidgetRoate();
    /*转动配置 setRoateIni
     * QJsonObject roateIni 里的参数配置
     * speed :每秒转动帧数 int
     * angle_x:每帧沿X轴转动角度(正数为顺时针，负数为逆时针) int
     * angle_y:每帧沿Y轴转动角度(正数为顺时针，负数为逆时针) int
     * angle_z:每帧沿Z轴转动角度(正数为顺时针，负数为逆时针) int
     * pos_x:X轴旋转中心点(不设置则是沿控件中心旋转) 0,0
     * pos_y:Y轴旋转中心点(不设置则是沿控件中心旋转) 0,0
     * pos_z:Z轴旋转中心点(不设置则是沿控件中心旋转) 0,0
     * range_x:X轴旋转范围(不设置则是360度旋转) 0,0
     * range_y:Y轴旋转范围(不设置则是360度旋转) 0,0
     * range_z:Z轴旋转范围(不设置则是360度旋转) 0,0
     * maxframe_x:X轴最大转动次数(不设置则是一直转) int
     * maxframe_y:Y轴最大转动次数(不设置则是一直转) int
     * maxframe_z:Z轴最大转动次数(不设置则是一直转) int
     * 例：setRoateIni({{"speed",50},{"angle_z",1}});
    */
    void setJsonIni(QJsonObject roateIni);
    void setRoateIni(QJsonObject roateIni);
private:

    struct ST_RoateIni{
        /*每帧转动角度*/
        int angle=0;
        /*最大转动次数*/
        int maxFrame=0;
        /*旋转中心点位置,不设置则是以控件中心旋转*/
        QPointF pos;
        /*角度转动范围*/
        SActiveRange range;
        /*当前转动次数*/
        int nowFrame=0;
    };
    struct{
        ST_RoateIni X;
        ST_RoateIni Y;
        ST_RoateIni Z;
        /*每秒转动帧数*/
        int speed=30;
    }m_RoateIni;

    QTransform getTransform(QGraphicsProxyWidget* grapWidget);
    int getAngle(int nowFrame, ST_RoateIni roateIni);

    int computeAngle(int range, SActiveRange roateRange);
    void SetTransform(QTransform &transform, ST_RoateIni &roateIni, QPointF centerPos, Qt::Axis axis);
signals:

};

#endif // CXANIMATEWIDGETROATE_H
