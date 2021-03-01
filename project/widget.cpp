#include "widget.h"
#include "ui_widget.h"
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QSvgGenerator>
#include <QPainter>
#include <QLabel>
#include <QTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSvgRenderer *renderer = new QSvgRenderer(QLatin1String("/Users/edz/Downloads/download-failure.svg"));

//    ui->widget_2->setRoateIni({{"speed",50},{"angle_z",-1},{"range_z","30,180"},{"maxframe_z",500}});
//    ui->widget_2->setRoateIni({{"speed",50},{"angle_z",5},{"range_z","30,180"}});
    ui->widget_2->setRoateIni({{"speed",20},{"angle_x",10},{"range_x","20,90"},{"angle_y",10},{"range_y","20,90"}});
    ui->pushButton_3->setFileName(QString("/Users/edz/Downloads/Close.svg"));
    ui->pushButton_3->setColors({{"hover","#fe5f55|#fff1c1"},{"click","red|yellow"}});
    ui->pushButton_3->setSVGModel(CXSVGPushButton::ESVGModel_Background);

    ui->pushButton_2->setFileName(QString("/Users/edz/Downloads/new.svg"));
    ui->pushButton_2->setSVGModel(CXSVGPushButton::ESVGModel_Background);


    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        ui->widget_4->start();
    });
    ui->widget_4->stop();
//    ui->widget_5->stop();
    this->update();
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::paintEvent(QPaintEvent *event)
//{
//    QSvgRenderer *renderer = new QSvgRenderer(QString("/Users/edz/Downloads/new.svg"),this);
//    QPainter p(this);
//    renderer->render(&p);
//}

