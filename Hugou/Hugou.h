#pragma once

#include <QWidget>
#include <QPainter>
#include <QSettings>
#include <windowsx.h>
#include <Windows.h>
#include <dwmapi.h>
#include "Var.h"
#include "ui_Hugou.h"
#include "Setting.h"
#include "SettingsHelper.h"

extern FloatingNoteManager floatingNoteManager;

class Hugou : public QWidget
{

    Q_OBJECT

public:
    Hugou(QWidget* parent = nullptr);
    ~Hugou();
    // ģ��Ч��
    QGraphicsBlurEffect* leftBlurEffect;
    QGraphicsBlurEffect* rightBlurEffect;
    QTimer blurTimer;

    void raiseReadingSettingError();
    void raiseSavingSettingError();
    void applyTheme(QString theme = "");

protected slots:
    void changeStackedWidget(int index);
    void openPDFEditFunction();
    void blur();
    void clearBlur();

private:
    int blurRadius = 0;
    int border = 10;
    bool isPressed = false;
    bool isScalable = true;
    Ui_HugouClass ui;
    QSettings settings;
    QPoint pressPos;
    QTimer* floatingNoteDelayTimer;
    enum Area
    {
        TOPLEFT,
        TOP,
        TOPRIGHT,
        LEFT,
        RIGHT,
        BOTTOMLEFT,
        BOTTOM,
        BOTTOMRIGHT,
        DRAGZONE,
        NOTAREA
    };
    Area area = NOTAREA;
    Area getArea(QPoint mousePos);
    QRect currentMainWindowGeometry;
    QRect customScale(Area area, QRect currentMainWindowGeometry, QPoint change);

    // ���ຯ����д
    // ע1�����ﲻ�ܼ�ʹ�����׷�ٵķ�ʽ���۲�����Ƿ�����ק��Ե�ϡ��ڵ�����뿪��Ե����ʱ�������ڵ���ϵ��
    //    ����Ҳ�����޷�һһ���ӿؼ�������׷�٣����Ӳ��ҽ������ܣ�����˵�����뿪��Ե����ʱ���������
    //    ʽ����ָ��糣��
    // ע2������������ʵ�ִ��ڱ�Ե����İ취����һ�ֽ���Windows APIʵ�֣��߱����񣻵ڶ�����ȫ��qtʵ�֣�
    //    ���Կ�ƽ̨���÷�����ĩβע�ʹ������ڱ������У������Windows API��
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
    void changeEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    //void showEvent(QShowEvent* event) override;

    // ��ȫ��qtʵ�ֵĴ��ڱ�Ե����취��
    //bool event(QEvent* event)
    //{
    //    if (event->type() == QEvent::HoverMove) {
    //        QHoverEvent* hoverEvent = static_cast<QHoverEvent*>(event);
    //        QPoint mousePos = hoverEvent->pos();
    //        if (!isMaximum && !isPressed)
    //        {
    //            edge = getEdge(mousePos);
    //            if (edge == TOP || edge == BOTTOM) { setCursor(Qt::SizeVerCursor); }
    //            if (edge == LEFT || edge == RIGHT) { setCursor(Qt::SizeHorCursor); }
    //            if (edge == TOPLEFT || edge == BOTTOMRIGHT) { setCursor(Qt::SizeFDiagCursor); }
    //            if (edge == TOPRIGHT || edge == BOTTOMLEFT) { setCursor(Qt::SizeBDiagCursor); }
    //            if (edge == NOTEDGE) { setCursor(Qt::ArrowCursor); }
    //        }
    //        //if (edge != NOTEDGE)
    //        //{
    //        //    QMouseEvent mouseEvent(QEvent::MouseMove, mousePos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
    //        //    mouseMoveEvent(&mouseEvent);
    //        //}
    //    }
    //    return QWidget::event(event);
    //}

    //void mousePressEvent(QMouseEvent* event)
    //{
    //    if (event->button() == Qt::LeftButton) {
    //        pressPos = event->globalPos();
    //        currentMainWindowGeometry = this->geometry();
    //        isPressed = true;
    //    }
    //    return QWidget::mousePressEvent(event);
    //}

    //void mouseReleaseEvent(QMouseEvent* event)
    //{
    //    isPressed = false;
    //    return QWidget::mouseReleaseEvent(event);
    //}

    //void mouseMoveEvent(QMouseEvent* event) override
    //{
    //    QPoint change = event->globalPos() - pressPos;
    //    QRect newMainWindowGeometry = customScale(edge, currentMainWindowGeometry, change);
    //    this->setGeometry(newMainWindowGeometry);
    //    return QWidget::mouseMoveEvent(event);
    //}
};