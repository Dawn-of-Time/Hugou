#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include "View/Include/FadeEffectButton.h"
#include "View/Include/View_MemoSetting.h"
#include "CheckBox.h"

class MemoWidget :
    public QWidget
{
    Q_OBJECT

public:
    MemoWidget(Memo* memo, QWidget* parent);
    MemoSettingView* getMemoSettingView() { return m_memoSetting; };

private:
    Memo* m_memo;
    QPropertyAnimation* m_memoSettingExpandAnimation;
    QPropertyAnimation* m_memoSettingCollapseAnimation;
    QVBoxLayout* m_layout;
    FadeEffectButton* m_memoBriefWidget;
    QHBoxLayout* m_memoBriefWidgetLayout;
    QPushButton* m_dropDownButton;
    CheckBox* m_checkBox;
    QWidget* m_memoContentWidget;
    QVBoxLayout* m_memoContentWidgetLayout;
    QLabel* m_memoContent;
    QLabel* m_memoSubContent;
    MemoSettingView* m_memoSetting;

    void setupUi();
    void showMemoSetting();
    void hideMemoSetting();
};

