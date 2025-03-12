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


// ʱ��


// ��Ҫ�Ժͽ����̶�
class MemoImportanceAndUrgencyItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoImportanceAndUrgencyItem(QWidget* parent = nullptr);

private:
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
};

// ��ϸ��Ϣ
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

// �ӱ���¼
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

// ����
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

// �ο���Դ
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

