#ifndef CXANIMATEWIDGET_H
#define CXANIMATEWIDGET_H

#include <QWidget>
#include <QJsonObject>
class QGraphicsView;
class QGraphicsScene;
class QGraphicsProxyWidget;
class QTimeLine;

struct SRoateRange{
    int min;
    int max;
    SRoateRange(int imin=0,int imax=0):min(imin),max(imax){
    };
    bool isEmply(){
        return min==0&&max==0;
    }
    int length(){
        return max-min;
    }
};

class CXAnimateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CXAnimateWidget(QWidget *parent = nullptr, QJsonObject JsonIni=QJsonObject());
    ~CXAnimateWidget();
    void paintEvent(QPaintEvent *event);
    void start();
    void stop();
    void setSpeed(const int speed);

    virtual void setRoateIni(QJsonObject jsonIni) =0;
private:
    virtual QTransform getTransform(QGraphicsProxyWidget *grapWidget) =0;
protected:
    void resizeEvent(QResizeEvent *event);
public slots:
    void onFrameChanged();
private:
    int m_frameNum;
    QTimeLine* m_pTimeLine;
    QGraphicsView* m_GraphView;
    QGraphicsScene *m_GrapScene;
    QList<QGraphicsProxyWidget*> m_listGrapWidget;
    QJsonObject m_JsonIni;

    QPointF StringToPoint(QString point);
    SRoateRange StringToRange(QString range);

    //增加窗口类型
    template<typename WidgetType>
    void AddGrapWidgetType();
signals:

};

#endif // CXANIMATEWIDGET_H
