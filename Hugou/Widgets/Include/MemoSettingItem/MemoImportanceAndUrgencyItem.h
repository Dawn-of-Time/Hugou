#pragma once
#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"

class MemoImportanceAndUrgencyItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoImportanceAndUrgencyItem(QWidget* parent = nullptr);

private:
    MemoImportanceAndUrgency m_memoImportanceAndUrgency = MemoImportanceAndUrgency::UrgentAndImportant;
    QVBoxLayout* m_contentLayout;
    QWidget* m_topWidget;
    QLabel* m_importantLabel;
    QWidget* m_middleWidget;
    QWidget* m_leftWidget;
    QLabel* m_notUrgentLabel;
    QWidget* m_matrixWidget;
    QPushButton* m_topLeftButton;
    QWidget* m_topLine;
    QPushButton* m_topRightButton;
    QWidget* m_leftLine;
    QWidget* m_centralLine;
    QWidget* m_rightLine;
    QPushButton* m_bottomLeftButton;
    QWidget* m_bottomLine;
    QPushButton* m_bottomRightButton;
    QWidget* m_rightWidget;
    QLabel* m_urgentLabel;
    QWidget* m_bottomWidget;
    QLabel* m_notImportantLabel;
    void setupUi();
    void select();
    void adjust(QPushButton* button);
};
