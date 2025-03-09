#pragma once
#include "Include/Struct_Memo.h"
#include "View/Include/View_MemoTypeConfig.h"
#include "MemoTypeWidget.h"
#include <QGraphicsEffect>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStyleOption>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

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

// 类型
class MemoTypeItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoTypeItem(const QList<MemoTypeLabel*>& typeLabelList, QMap<int, QList<MemoType*>>& typeLabelMap, QList<MemoType*>& typeList, QWidget* parent = nullptr);
    void addMemoType(MemoType& memoType);

private:
    QMap<int, QList<MemoType*>>& m_typeLabelMap;
    const QList<MemoTypeLabel*>& m_typeLabelList;
    QList<MemoType*>& m_typeList;
    int m_count = 0;
    QMap<MemoType*, MemoTypeWidget*> m_memoTypeWidgetMap;
    QList<MemoType*> m_priorityTypeList;
    QMap<MemoType*, MemoType*> m_oldNewPriorityDisplayMemoTypeMap = {};
    QMap<MemoType*, MemoType*> m_oldNewMemoTypeMap = {};
    QHBoxLayout* m_contentLayout;
    QWidget* m_typeListWidget;
    QHBoxLayout* m_typeListWidgetLayout;
    QPushButton* m_addTypeButton;
    void setupUi();
    void showMemoTypeConfigView();
};

// 时间
class MemoTimeItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoTimeItem(QWidget* parent = nullptr);
    ~MemoTimeItem();
    void loadMonthView(QDate date);

private:
    bool m_hasReminder = false;
    QParallelAnimationGroup* m_animationGroup;
	QVBoxLayout* m_contentLayout;
	QWidget* m_reminderWidget;
    QPushButton* m_reminderButton;
    QPushButton* m_off;
    QPushButton* m_moreButton;
    QGraphicsOpacityEffect* m_moreButtonEffect;
    QWidget* m_dateWidget;
    QVBoxLayout* m_dateWidgetLayout;
    QWidget* m_dateTitleWidget;
    QHBoxLayout* m_dateTitleWidgetLayout;
    QLabel* m_dateTitle;
    QWidget* m_actionWidget;
    QHBoxLayout* m_actionWidgetLayout;
    QPushButton* m_backButton;
    QPushButton* m_forwardButton;
    QWidget* m_monthWidget;
    QVBoxLayout* m_monthWidgetLayout;
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QWidget* m_timeWidget;
	QHBoxLayout* m_timeWidgetLayout;
    QWidget* m_startTimeWidget;
	QVBoxLayout* m_startTimeWidgetLayout;
	QWidget* m_startTimeYYYYMMDDWidget;
	QHBoxLayout* m_startTimeYYYYMMDDWidgetLayout;
    QPushButton* m_startTimeYearButton;
	QPushButton* m_startTimeMonthButton;
	QPushButton* m_startTimeDayButton;
	QWidget* m_startTimeHHMMWidget;
	QHBoxLayout* m_startTimeHHMMWidgetLayout;
	QPushButton* m_startTimeHourButton;
	QPushButton* m_startTimeMinuteButton;
    QLabel* m_toLabel;
	QWidget* m_endTimeWidget;
	QVBoxLayout* m_endTimeWidgetLayout;
	QWidget* m_endTimeYYYYMMDDWidget;
	QHBoxLayout* m_endTimeYYYYMMDDWidgetLayout;
	QPushButton* m_endTimeYearButton;
	QPushButton* m_endTimeMonthButton;
	QPushButton* m_endTimeDayButton;
	QWidget* m_endTimeHHMMWidget;
	QHBoxLayout* m_endTimeHHMMWidgetLayout;
	QPushButton* m_endTimeHourButton;
	QPushButton* m_endTimeMinuteButton;

    QList<QPushButton*> m_weekIndexButtonListForAMonth = {};
    QList<QPushButton*> m_dayListForAMonth = {};
    QList<QWidget*> m_weekListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    
    void setupUi();
    void switchReminder();
    void enableGraphicsEffect();
	void disableGraphicsEffect();
};

// 重要性和紧急程度
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

