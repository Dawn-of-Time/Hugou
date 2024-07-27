#pragma once

#include <QWidget>
#include <QPainter>
#include "Var.h"
#include "ui_Hugou.h"
#include "PDFEdit.h"
#include "Setting.h"

class Hugou : public QWidget
{

    Q_OBJECT

public:
    Hugou(Setting* setting, QWidget* parent = nullptr);
    ~Hugou();
    Setting* receiveSetting;
    PDFEdit* pdfEdit;
    Ui_HugouClass ui;
    // 模糊效果
    QGraphicsBlurEffect* blurEffect;
    QTimer blurTimer;
    void switchOverSearchButton(bool msg);
    void search();
    void raiseReadingSettingError();
    void raiseSavingSettingError();

protected slots:
    void changeStackedWidget(int index);
    void checkIsLineEditNull();
    void deleteSearchText();
    void openPDFEditFunction();
    void blurStackedWidget();
    void clearStackedWidget();

private:
    int blurRadius = 0;
    bool isPressed = false;
    bool isScalable = true;
    QPoint pressPos;
    enum Edge
    {
        TOPLEFT,
        TOP,
        TOPRIGHT,
        LEFT,
        RIGHT,
        BOTTOMLEFT,
        BOTTOM,
        BOTTOMRIGHT,
        NOTEDGE
    };
    Edge edge = NOTEDGE;
    Edge getEdge(QPoint mousePos);
    QRect currentMainWindowGeometry;
    QRect customScale(Edge edge, QRect currentMainWindowGeometry, QPoint change);
    //void mousePressEvent(QMouseEvent* event) override {
    //    mousePos = event->pos();
    //}

    // 注：这里不能简单使用鼠标追踪的方式来观察鼠标是否处于拖拽边缘上。在当鼠标离开边缘区域时，由于遮挡关系，
    //    并且也由于无法一一将子控件添加鼠标追踪（冗杂并且降低性能），因此当鼠标离开边缘区域时，鼠标光标样
    //    式不会恢复如常。
    bool event(QEvent* event)
    {
        if (event->type() == QEvent::HoverMove) {
            QHoverEvent* hoverEvent = static_cast<QHoverEvent*>(event);
            QPoint mousePos = hoverEvent->pos();
            if (!isMaximum && !isPressed)
            {
                edge = getEdge(mousePos);
                if (edge == TOP || edge == BOTTOM) { setCursor(Qt::SizeVerCursor); }
                if (edge == LEFT || edge == RIGHT) { setCursor(Qt::SizeHorCursor); }
                if (edge == TOPLEFT || edge == BOTTOMRIGHT) { setCursor(Qt::SizeFDiagCursor); }
                if (edge == TOPRIGHT || edge == BOTTOMLEFT) { setCursor(Qt::SizeBDiagCursor); }
                if (edge == NOTEDGE) { setCursor(Qt::ArrowCursor); }
            }
            //if (edge != NOTEDGE)
            //{
            //    QMouseEvent mouseEvent(QEvent::MouseMove, hoverEvent->pos(),Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            //    mouseMoveEvent(&mouseEvent);
            //}
        }
        return QWidget::event(event);
    }

    void mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton) {
            pressPos = event->globalPos();
            currentMainWindowGeometry = this->geometry();
            isPressed = true;
        }
        return QWidget::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        isPressed = false;
        return QWidget::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event)
    {
        QPoint change = event->globalPos() - pressPos;
        QRect newMainWindowGeometry = customScale(edge, currentMainWindowGeometry, change);
        if (newMainWindowGeometry.width() >= mainWindowWidth && newMainWindowGeometry.height() >= mainWindowHeight)
        {
            this->setGeometry(newMainWindowGeometry);
        }
        return QWidget::mouseMoveEvent(event);
    }
};
