#pragma once

#include <QtCore/QVariant>
#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QFont>
#include <windowsx.h>
#include <Windows.h>
#include <dwmapi.h>
#include "View_TitleBar.h"
#include "View_AsideBar.h"
#include "View_Settings.h"
#include "Const.h"
#include "ButtonHoverWatcher.h"
#include "ComboboxWheelWatcher.h"
#include "WorkSpace.h"
#include "FloatingNotePanel.h"
#include "GlobalTop.h"

QT_BEGIN_NAMESPACE

class HugouController;

class HugouView : public QWidget
{
    Q_OBJECT

public:
    HugouView();

protected slots:
    void blur();
    void clearBlur();

private:
    friend class HugouController;
    QVBoxLayout* m_generalLayout;
    QWidget* m_asideBarAndStackedWidget;
    QHBoxLayout* m_asideBarAndStackedLayout;
    TitleBarView* m_titleBarView;
    AsideBarView* m_asideBarView;
    QWidget* m_stackedWidgetContainer;
    QStackedWidget* m_stackedWidget;
    QHBoxLayout* m_stackedWidgetLayout;
    WorkSpace* m_workSpaceWidget;
    SettingsView* m_settingsView;
    QWidget* m_blurWidget;
    QGraphicsBlurEffect* m_blurEffect;
    FloatingNotePanel* m_floatingNotePanel;
    GlobalTop* m_globalTop;
    QPixmap m_screenShot;
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
    Area m_area = NOTAREA;
    QRect m_currentMainWindowGeometry;
    QRect customScale(Area area, QRect currentMainWindowGeometry, QPoint change);
    Area getArea(QPoint mousePos);
    void setupUi();
    void startToApplyThemeResource(QString theme);
    bool applyThemeResource(QString generalStyleFile, QString asideBarStyleFile, QString settingsStyleFile);
    void endToApplyThemeResourceFinished();
    void changeStackedWidgetRequest(int index);
    void retranslateUi();
    // 父类函数重写
    // 注1：这里不能简单使用鼠标追踪的方式来观察鼠标是否处于拖拽边缘上。在当鼠标离开边缘区域时，由于遮挡关系，
    //    并且也由于无法一一将子控件添加鼠标追踪（冗杂并且降低性能），因此当鼠标离开边缘区域时，鼠标光标样
    //    式不会恢复如常。
    // 注2：以下是两种实现窗口边缘拉伸的办法，第一种借助Windows API实现，具备其风格；第二种完全由qt实现，
    //    可以跨平台（该方法见末尾注释处）。在本工程中，多采用Windows API。
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
    void changeEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;


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

QT_END_NAMESPACE
