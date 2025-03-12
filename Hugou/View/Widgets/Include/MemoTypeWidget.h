#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "Include/Struct_Memo.h"
#include "Widgets/Include/ToolTip.h"

QT_BEGIN_NAMESPACE

class MemoTypeWidget :
    public QPushButton
{
    Q_OBJECT

public:
    MemoTypeWidget(MemoType& memoType, QWidget* parent);
    void updateUi(const MemoType& newType);
    void setStatus(bool status = true);
    MemoType& getMemo() { return m_memoType; }

private:
    bool m_status = false;
    MemoType& m_memoType;
    QVBoxLayout* m_layout;
    QLabel* m_icon;
    QLabel* m_type;
    QWidget* m_mask;
    QGraphicsOpacityEffect* m_maskEffect;
    ToolTip* m_tooltip = nullptr;
    void setupUi();
    void showEvent(QShowEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
};

QT_END_NAMESPACE
