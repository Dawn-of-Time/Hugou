#pragma once

#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTextEdit>
#include <QLineEdit>
#include "Include/Struct_Memo.h"

class MemoSettingItem :
    public QWidget
{
    Q_OBJECT
public:
    MemoSettingItem(QWidget* parent = nullptr);

protected:
    QWidget* m_content;
    QVBoxLayout* m_itemLayout;
    QWidget* m_titleWidget;
    QHBoxLayout* m_titleLayout;
    QLabel* m_title;
    
private:
    friend class MemoSettingController;

    void setupUi();
    void paintEvent(QPaintEvent* event) override;
};

// 详细信息
class MemoDetailItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoDetailItem(QWidget* parent = nullptr);
    void adjustToOptimalSize();

private:
    void setupUi();
    QVBoxLayout* m_contentLayout;
    QTextEdit* m_detail;
};

// 子备忘录
class MemoSubMemoItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoSubMemoItem(QWidget* parent = nullptr);

private:
    int m_count = 0;
    void setupUi();
    QVBoxLayout* m_contentLayout;
    QWidget* m_addSubMemoWidget;
    QHBoxLayout* m_addSubMemoWidgetLayout;
    QLabel* m_subMemoNumber;
    QLineEdit* m_subMemoContent;
};

// 奖励
class MemoAwardItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoAwardItem(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_contentLayout;
    QLabel* m_addAwardContent;
    QLabel* m_addAwardSubContent;
    void setupUi();
};

// 参考资源
class MemoReferenceItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoReferenceItem(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_contentLayout;
    QLabel* m_addReferenceContent;
    QLabel* m_addReferenceSubContent;
    void setupUi();
};

