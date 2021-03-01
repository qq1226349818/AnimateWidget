#ifndef CXSVGPUSHBUTTON_H
#define CXSVGPUSHBUTTON_H

#include <QPushButton>
#include <QJsonObject>
#include <QSvgRenderer>
class QSvgRenderer;
class QDomElement;
class QGraphicsColorizeEffect;
class CXSVGPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum EButtonStatus{
        EButtonStatus_Normal,
        EButtonStatus_Hovered,
        EButtonStatus_Clicked
    };
    enum ESVGModel{
        ESVGModel_Icon,
        ESVGModel_Background
    };

    /*设置svg颜色状态变化 objColors 颜色分割符"|"
     * normal:默认状态下SVG里需要变化颜色，如果没有则是全部替换
     * hover:hover状态下SVG里改变的颜色，与默认状态下颜色依次对应
     * click:click状态下SVG里改变的颜色，与默认状态下颜色依次对应
     *例:setColors({{"normal","#FF3E69|#FF1D3F"},{"hover","#fe5f55|#fff1c1"},{"click","red|yellow"}})
*/
    CXSVGPushButton(QString filename,QJsonObject objColors,ESVGModel svgModel=ESVGModel_Icon, QWidget *parent = nullptr);
    CXSVGPushButton(QWidget *parent = nullptr,ESVGModel svgModel=ESVGModel_Icon);
    ~CXSVGPushButton();
public:
    void iniData();
    void SVGPaint();
    void SVGUpdate();

    void setFileName(QString fileName);
    void setSVGModel(ESVGModel svgmodel);
    void setInIni(QString fileName,QJsonObject objcolors);
    void setColors(QJsonObject objcolors);
    void setSVGColor(QStringList newColors,EButtonStatus buttonst);

    QIcon SVGRenderToIcon(QSvgRenderer &svgRender);

private:
    QString m_fileName;
    QJsonObject m_JsonColors;
    QHash<EButtonStatus,QStringList> m_hashColor;
    QHash<EButtonStatus,QSvgRenderer*> m_hashSVGRender;
    QHash<EButtonStatus,QIcon> m_hashIcon;
    QByteArray m_ByteData;
    EButtonStatus m_statusNow;
    ESVGModel m_svgModel;


    void SetAttrRecur(QDomElement elem, QString strtagname, QString strattr, QString strattrval);
    QStringList splitColorList(QString strColors);
    void writeSVGHash(EButtonStatus buttonst, QByteArray bytedata);
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);
};


#endif // CXSVGPUSHBUTTON_H
