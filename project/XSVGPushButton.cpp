#include "XSVGPushButton.h"
#include <QGraphicsColorizeEffect>
#include <QResizeEvent>
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

CXSVGPushButton::CXSVGPushButton(QString filename, QJsonObject objColors, ESVGModel svgModel, QWidget *parent):m_fileName(filename),m_JsonColors(objColors),m_svgModel(svgModel),QPushButton(parent){
    this->setFlat(true);
    this->setCursor(QCursor(Qt::PointingHandCursor));
    setInIni(filename,m_JsonColors);
}

CXSVGPushButton::CXSVGPushButton(QWidget *parent,ESVGModel svgModel):m_svgModel(svgModel),QPushButton(parent)
{
    this->setFlat(true);
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

CXSVGPushButton::~CXSVGPushButton()
{
    m_hashColor.clear();
    m_hashSVGRender.clear();
    m_hashIcon.clear();
}

void CXSVGPushButton::setInIni(QString fileName,QJsonObject objcolors)
{
    m_fileName.swap(fileName);
    m_JsonColors.swap(objcolors);
    SVGUpdate();
}

void CXSVGPushButton::setColors(QJsonObject objcolors)
{
    m_JsonColors.swap(objcolors);
    SVGUpdate();
}

void CXSVGPushButton::setSVGColor(QStringList newColors, CXSVGPushButton::EButtonStatus buttonst)
{
    QStringList defColorList=m_hashColor.value(EButtonStatus_Normal);
    QByteArray ByteData=m_ByteData;
    if(newColors.isEmpty())
        return;
    if(defColorList.isEmpty()){
        QDomDocument doc;
        doc.setContent(ByteData);
        SetAttrRecur(doc.documentElement(), "path", "fill", newColors.first());
        writeSVGHash(buttonst,doc.toByteArray());
    }
    else{
        for(int i=0;i<defColorList.length();i++)
        {
            if(i<newColors.length()){
                if(defColorList[i].isEmpty()||newColors[i].isEmpty())
                    continue;
                ByteData.replace(defColorList[i],newColors[i].toLatin1()+"#lql#");
                qDebug()<<"ChangeColor:"<<defColorList[i]<<newColors[i];
            }
        }
        ByteData.replace("#lql#","");
        writeSVGHash(buttonst,ByteData);
    }
}

void CXSVGPushButton::setFileName(QString fileName)
{
    m_fileName.swap(fileName);
    SVGUpdate();
}

void CXSVGPushButton::setSVGModel(CXSVGPushButton::ESVGModel svgmodel)
{
    m_svgModel=svgmodel;
    switch (m_svgModel) {
    case ESVGModel_Icon:{
    }break;
    case ESVGModel_Background:{
        this->setStyleSheet("QPushButton{background:transparent}");
    }break;
    default:
        break;
    };
    SVGPaint();
}

QIcon CXSVGPushButton::SVGRenderToIcon(QSvgRenderer &svgRender)
{
    QPixmap pix(this->iconSize());
    pix.fill(Qt::transparent);
    QPainter pixPainter(&pix);
    svgRender.render(&pixPainter);
    QIcon svgicon(pix);
    return svgicon;
}

QStringList CXSVGPushButton::splitColorList(QString strColors)
{
    QStringList listColor=strColors.split("|");
    bool isEmply=true;
    foreach (auto color, listColor) {
        if(color!="")
            isEmply=false;
    }
    if(isEmply)
        return QStringList();
    else
        return listColor;
}

void CXSVGPushButton::writeSVGHash(CXSVGPushButton::EButtonStatus buttonst, QByteArray bytedata)
{
    QSvgRenderer *svgRenderer=new QSvgRenderer(bytedata,this);
    m_hashSVGRender.insert(buttonst,svgRenderer);
    m_hashIcon.insert(buttonst,SVGRenderToIcon(*svgRenderer));
}

void CXSVGPushButton::iniData()
{
    QFile file(m_fileName);
    file.open(QIODevice::ReadOnly);
    m_ByteData = file.readAll();
    file.close();

    writeSVGHash(EButtonStatus_Normal,m_ByteData);

    QString strListNormal=m_JsonColors["normal"].toString();
    QString strListHover=m_JsonColors["hover"].toString();
    QString strListClick=m_JsonColors["click"].toString();

    m_hashColor.insert(EButtonStatus_Normal,splitColorList(strListNormal));
    m_hashColor.insert(EButtonStatus_Hovered,splitColorList(strListHover));
    m_hashColor.insert(EButtonStatus_Clicked,splitColorList(strListClick));

    setSVGColor(m_hashColor[EButtonStatus_Hovered], EButtonStatus_Hovered);
    setSVGColor(m_hashColor[EButtonStatus_Clicked], EButtonStatus_Clicked);
}

void CXSVGPushButton::SVGUpdate()
{
    iniData();
    SVGPaint();
}

void CXSVGPushButton::SVGPaint()
{
    switch (m_svgModel) {
    case ESVGModel_Icon:{
            this->setIcon(m_hashIcon[m_statusNow]);
        if(m_hashIcon[m_statusNow].isNull())
            this->setIcon(m_hashIcon[EButtonStatus_Normal]);
    }break;
    case ESVGModel_Background:{
        this->setIcon(QIcon());
    }break;
    default:
        break;
    };
    update();
}

void CXSVGPushButton::SetAttrRecur(QDomElement elem, QString strtagname, QString strattr, QString strattrval)
{
    // if it has the tagname then overwritte desired attribute
    if (elem.tagName().compare(strtagname) == 0)
    {
        elem.setAttribute(strattr, strattrval);
    }
    // loop all children
    for (int i = 0; i < elem.childNodes().count(); i++)
    {
        if (!elem.childNodes().at(i).isElement())
        {
            continue;
        }
        SetAttrRecur(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
    }
}

void CXSVGPushButton::resizeEvent(QResizeEvent *event)
{
    this->setIconSize(event->size());
    QPushButton::resizeEvent(event);
    SVGPaint();
}

void CXSVGPushButton::mousePressEvent(QMouseEvent *event)
{
    m_statusNow=EButtonStatus_Clicked;
    QPushButton::mousePressEvent(event);
    SVGPaint();
}

void CXSVGPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_statusNow=EButtonStatus_Hovered;
    QPushButton::mouseReleaseEvent(event);
    SVGPaint();
};

void CXSVGPushButton::enterEvent(QEvent *event)
{
    m_statusNow=EButtonStatus_Hovered;
    QPushButton::enterEvent(event);
    SVGPaint();
}

void CXSVGPushButton::leaveEvent(QEvent *event)
{
    m_statusNow=EButtonStatus_Normal;
    QPushButton::leaveEvent(event);
    SVGPaint();
}


void CXSVGPushButton::paintEvent(QPaintEvent *event)
{
    switch (m_svgModel) {
    case ESVGModel_Background:{
        QPainter paint(this);
        if(m_hashSVGRender[m_statusNow])
            m_hashSVGRender[m_statusNow]->render(&paint);
        else if(m_hashSVGRender[EButtonStatus_Normal])
            m_hashSVGRender[EButtonStatus_Normal]->render(&paint);
        paint.end();
    }break;
    default:
        break;
    }
    QPushButton::paintEvent(event);
}
