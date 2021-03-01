#include "XDragWidget.h"
#include "ui_XDragWidget.h"
#include <QStyleOption>
#include <QPainter>
XDragWidget::XDragWidget(QWidget *parent) :
    QWidget(parent),m_isPress(false),m_isMax(false),
    ui(new Ui::XDragWidget)
{
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
//    this->setObjectName("XDragWidget");
//    this->setStyleSheet("QWidget{background-color:blue}");
//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    //设置阴影距离
//    shadow->setOffset(4, 8);
//    //设置阴影颜色
//    shadow->setColor(QColor(0,0,0,20));
//    //设置阴影圆角
//    shadow->setBlurRadius(50);
//    //给嵌套QWidget设置阴影
//    this->setGraphicsEffect(shadow);
}

XDragWidget::~XDragWidget()
{
    delete ui;
}

void XDragWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        m_isPress=true;
        m_point=event->globalPos()-this->window()->pos();
    }
    QWidget::mousePressEvent(event);
}

void XDragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        m_isPress=false;
    }
    QWidget::mouseReleaseEvent(event);
}

void XDragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPress){
        QPoint pos_move=event->globalPos();
        this->move(pos_move-m_point);
    }
    QWidget::mouseMoveEvent(event);
}

void XDragWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_isMax=m_isMax?false:true;
    if(m_isMax)
        setWindowState(Qt::WindowMaximized);
    else
        setWindowState(Qt::WindowNoState);
    QWidget::mouseDoubleClickEvent(event);
}

void XDragWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
    QWidget::paintEvent(event);

}
