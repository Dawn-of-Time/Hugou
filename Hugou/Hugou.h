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
    // 模糊效果
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

    // 父类函数重写
    // 注1：这里不能简单使用鼠标追踪的方式来观察鼠标是否处于拖拽边缘上。在当鼠标离开边缘区域时，由于遮挡关系，
    //    并且也由于无法一一将子控件添加鼠标追踪（冗杂并且降低性能），因此当鼠标离开边缘区域时，鼠标光标样
    //    式不会恢复如常。
    // 注2：以下是两种实现窗口边缘拉伸的办法，第一种借助Windows API实现，具备其风格；第二种完全由qt实现，
    //    可以跨平台（该方法见末尾注释处）。在本工程中，多采用Windows API。
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
    void changeEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    //void showEvent(QShowEvent* event) override;

    // 完全由qt实现的窗口边缘拉伸办法。
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