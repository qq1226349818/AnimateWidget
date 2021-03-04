#include "XAnimateWidget-Move.h"
#include <QString>
#include <QDebug>
CXAnimateWidgetMove::CXAnimateWidgetMove(QWidget *parent, QJsonObject roateIni):CXAnimateWidget(parent,roateIni),m_back(false)
{

}

CXAnimateWidgetMove::~CXAnimateWidgetMove()
{

}
//* move:16,20 -16,5;
//     * time:3 3 2
//     * maxframe:8
void CXAnimateWidgetMove::setJsonIni(QJsonObject jsonIni)
{
    m_JsonIni.swap(jsonIni);
    m_maxFrame=m_JsonIni["maxframe"].toInt();
    m_loopTimeMax=m_JsonIni["loop"].toInt();
    if(m_loopTimeMax==0)
        m_isLoop=false,m_loopTimeMax=1;
    else
        m_isLoop=true;
    QStringList listMove=m_JsonIni["move"].toString().split(" ");
    QStringList listTime=m_JsonIni["time"].toString().split(" ");
    if(listMove.length()!=listTime.length()){
        qDebug()<<"move and time length diffrent";
        return;
    }
    for(int i=0;i<listMove.length();i++){
        ST_MoveIni moveini;
        if(i>0)
            moveini.move_begin=m_listMoveIni.at(i-1).move_end;
        else
            moveini.move_begin=QPointF(0,0);
        moveini.move_end=StringToPoint(listMove.at(i));
        moveini.frame=listTime.at(i).toInt();
        moveini.move_speed=(moveini.move_end-moveini.move_begin)/moveini.frame;

        m_listMoveIni.append(moveini);
    }
}

QTransform CXAnimateWidgetMove::getTransform(QGraphicsProxyWidget *grapWidget)
{
    if((m_maxFrame<m_frameNum&&m_maxFrame!=0)||(m_loopTime>=m_loopTimeMax&&m_loopTimeMax!=-1))
        stop();
    QTransform transform;
    if(!grapWidget)
        return transform;
//    transform=grapWidget->transform();
    SetTransform(transform,getMoveIni());
    return transform;
}

void CXAnimateWidgetMove::SetTransform(QTransform &transform, CXAnimateWidgetMove::ST_MoveIni &scaleIni)
{
    if((m_loopTime>=m_loopTimeMax&&m_loopTimeMax!=-1)||(m_back&&!m_isLoop))
    {
    transform.translate(scaleIni.move_now.x(),scaleIni.move_now.y());
    return;
    }
    if(!m_back){
        scaleIni.move_now+=scaleIni.move_speed;
    }
    else{
        scaleIni.move_now-=scaleIni.move_speed;
    }
//    qDebug()<<"scaleIni.move_now:"<<scaleIni.move_now<<scaleIni.move/scaleIni.frame;
    transform.translate(scaleIni.move_now.x(),scaleIni.move_now.y());
    scaleIni.frame_now++;
    if(scaleIni.frame_now==scaleIni.frame){
    if(!m_back)
        m_index++,scaleIni.move_now=scaleIni.move_end;
    else
        m_index--,scaleIni.move_now=scaleIni.move_begin;

    getMoveIni().move_now=scaleIni.move_now;

    scaleIni.frame_now=0;
    }

}

CXAnimateWidgetMove::ST_MoveIni& CXAnimateWidgetMove::getMoveIni()
{
    static ST_MoveIni moveIni;
    if(m_listMoveIni.isEmpty())
        return moveIni;

    if(m_index<0)
        m_back=false,m_index=0,m_loopTime++;
    else if(m_index>m_listMoveIni.length()-1)
        m_back=true,m_index=m_listMoveIni.length()-1;

    return m_listMoveIni[m_index];
}
