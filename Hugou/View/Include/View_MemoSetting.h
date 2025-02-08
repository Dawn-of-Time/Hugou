#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxlayout>
#include <QLabel>
#include <QPushButton>
#include "Struct_Memo.h"

class MemoSettingView :
    public QWidget
{
public:
    MemoSettingView(QWidget* parent, Memo memo);
    void applyTemplate(MemoTemplate memoTemplate);
    void addMemoSettingItem(MemoSettingItemType itemType);

private:
    QVBoxLayout* m_layout;
    QWidget* m_templateWidget;
    QHBoxLayout* m_templateWidgetLayout;
    QLabel* m_templateTitle;
    QPushButton* m_templateButton;
    QWidget* m_contentWidget;
    QHBoxLayout* m_contentWidgetLayout;
    QMap<MemoSettingItemType, QWidget*> m_memoContentMap = {};

    void setupUi();

    class MemoSettingItem :
        public QWidget
    {
    public:
        MemoSettingItem(QWidget* parent);
        void setTitle(QString title);
        void setContent(QWidget* content);
        QWidget* m_content;

    private:
        friend class MemoSettingController;
        QVBoxLayout* m_itemLayout;
        QLabel* m_title;

        void setupUi();
    };

    // ����
    class MemoTypeItem :
        public MemoSettingItem
    {
    public:
        MemoTypeItem(QWidget* parent);

    private:
        QHBoxLayout* m_contentLayout;
        QList<QWidget*> m_memoTypeWidgetList;
        void setupUi();
        void addMemoType(MemoType memoType);
    };

    // ʱ��
    class MemoTimeItem :
        public MemoSettingItem
    {
    public:
        MemoTimeItem(QWidget* parent);

    private:
        void setupUi();
    };

    // ��Ҫ��
    class MemoImportanceItem :
        public MemoSettingItem
    {
    public:
        MemoImportanceItem(QWidget* parent);

    private:
        void setupUi();
    };

    // ��ϸ��Ϣ
    class MemoDetailItem :
        public MemoSettingItem
    {
    public:
        MemoDetailItem(QWidget* parent);

    private:
        void setupUi();
    };

    // �ӱ���¼
    class MemoSubMemoItem :
        public MemoSettingItem
    {
    public:
        MemoSubMemoItem(QWidget* parent);

    private:
        void setupUi();
    };

    // ����
    class MemoAwardItem :
        public MemoSettingItem
    {
    public:
        MemoAwardItem(QWidget* parent);

    private:
        void setupUi();
    };

    // �ο���Դ
    class MemoReferenceItem :
        public MemoSettingItem
    {
    public:
        MemoReferenceItem(QWidget* parent);

    private:
        void setupUi();
    };
};

