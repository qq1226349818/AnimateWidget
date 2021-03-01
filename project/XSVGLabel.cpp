#include "XSVGLabel.h"
#include <QSvgRenderer>
#include <QPainter>
CXSVGLabel::CXSVGLabel(const QString filename,QWidget *parent):m_filename(filename),QLabel(parent)
{

}

CXSVGLabel::CXSVGLabel(QWidget *parent):QLabel(parent)
{

}

CXSVGLabel::~CXSVGLabel()
{

}

void CXSVGLabel::setFileName(QString filename)
{
    m_filename.swap(filename);
    update();
}

void CXSVGLabel::setText(QString text)
{
    m_filename.swap(text);
    update();
}


void CXSVGLabel::paintEvent(QPaintEvent *event)
{
    QSvgRenderer *renderer = new QSvgRenderer(m_filename,this);
    QPainter p(this);
    renderer->render(&p);
}
