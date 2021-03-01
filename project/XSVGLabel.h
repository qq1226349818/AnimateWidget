#ifndef CXSVGLABEL_H
#define CXSVGLABEL_H

#include <QLabel>

class CXSVGLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CXSVGLabel(const QString filename,QWidget *parent = nullptr);
    explicit CXSVGLabel(QWidget *parent = nullptr);
    ~CXSVGLabel();
    void setFileName(QString filename);
    void setText(QString text);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString m_filename;
};

#endif // CXSVGLABEL_H
