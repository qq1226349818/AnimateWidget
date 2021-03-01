#ifndef XDRAGWIDGET_H
#define XDRAGWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
namespace Ui {
class XDragWidget;
}

class XDragWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XDragWidget(QWidget *parent = nullptr);
    ~XDragWidget();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    Ui::XDragWidget *ui;
    QPoint m_point;
    bool m_isPress;
    bool m_isMax;
};

#endif // XDRAGWIDGET_H
