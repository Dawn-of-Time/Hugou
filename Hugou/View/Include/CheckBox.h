#pragma once
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsEffect>
#include "Include/Const_Geometry.h"

class CheckBox : public QPushButton {
    Q_OBJECT

public:
    enum Status {
        Checked, Unchecked
    };
    CheckBox(QWidget* parent, Status status = Status::Unchecked);

signals:
    void SignalBorderProgressChanged();

private:
    Status m_status;
    QPropertyAnimation* m_animation;
    QVBoxLayout* m_layout;
    QPushButton* m_icon;
    QGraphicsOpacityEffect* m_effect;
    void changeStatus();
    void enableGraphicsEffect();
    void disableGraphicsEffect();
};