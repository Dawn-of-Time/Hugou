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
    // ģ��Ч��
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

    // ע�����ﲻ�ܼ�ʹ�����׷�ٵķ�ʽ���۲�����Ƿ�����ק��Ե�ϡ��ڵ�����뿪��Ե����ʱ�������ڵ���ϵ��
    //    ����Ҳ�����޷�һһ���ӿؼ�������׷�٣����Ӳ��ҽ������ܣ�����˵�����뿪��Ե����ʱ���������
    //    ʽ����ָ��糣��
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
