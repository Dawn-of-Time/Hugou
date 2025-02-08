#pragma once

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QWidgetAction>
#include <QFile>
#include <math.h>
#include <QTextLayout>
#include "ButtonHoverWatcher.h"
#include "Assistance_PreferenceHelper.h"
#include "PreferenceItem.h"

QT_BEGIN_NAMESPACE

class PreferenceController;

class PreferenceView : public QWidget
{
    Q_OBJECT

public:
    PreferenceView(QWidget* parent);
    ~PreferenceView();
    void adjustSizeHint();

protected slots:
    void checkIsLineEditNull();
    void deleteSearchText();

private:
    const QString searchText = QString(tr("Search item."));
    friend class PreferenceController;
    QHBoxLayout* m_preferenceLayout;
    QWidget* m_preferenceLeftWidget;
    QVBoxLayout* m_preferenceLeftLayout;
    QLineEdit* m_searchLineEdit;
    QPushButton* m_searchButton;
    QPushButton* m_searchDeletedButton;
    ButtonHoverWatcher* m_searchButtonHoverWatcher;
    ButtonHoverWatcher* m_searchDeletedButtonHoverWatcher;
    QStackedWidget* m_preferenceTreeStackedWidget;
    QVBoxLayout* m_preferenceTreeLayout;
    QTreeWidget* m_preferenceTreeWidget;
    QLabel* m_searchpreferenceNullLabel;
    QWidget* m_preferenceRightWidget;
    QVBoxLayout* m_preferenceRightLayout;
    QListWidget* m_preferenceContentListWidget;
    PreferenceItem::PreferenceMap m_preferenceMap;
    const QList<PreferenceItem*> m_preferenceItemList =
    {
        new LabelTitleItem("Common", PreferenceItem::Level::First),
        new LabelTitleItem("Appearance", PreferenceItem::Level::Second),
        new LabelTitleItem("Theme", PreferenceItem::Level::Third),
        new ComboboxItem("theme", preferenceValueMap["theme"]),
        new LabelHintItem("I will be launching the theme preview feature in the near future."),
        new SectionSpaceItem(),
        new LabelTitleItem("Country/Region", PreferenceItem::Level::Second),
        new LabelTitleItem("Language", PreferenceItem::Level::Third),
        new ComboboxItem("language", preferenceValueMap["language"]),
        new LabelHintItem("More and more languages are getting support. The language currently in the pipeline is: Chinese."),
        new ChapterSpaceItem(),

        new LabelTitleItem("Task", PreferenceItem::Level::First),
        new LabelTitleItem("Recycle Bin", PreferenceItem::Level::Second),
        new LabelTitleItem("Enable", PreferenceItem::Level::Third),
        new ComboboxItem("recycleBin", preferenceValueMap["recycleBin"]),
        new LabelHintItem("Enable this feature: When you delete a task, it will be moved to the recycle bin and completely destroyed after retention period."),
        new LabelTitleItem("Retention Period", PreferenceItem::Level::Third),
        new LineEditItem("retentionPeriod", new QIntValidator(1, 30)),
        new LabelHintItem("Set the number of days you expect to retain. Limit it to 1-30."),
        new ChapterSpaceItem()
    };

    void setupUi();
    void formTree();
    void formContentList();
    void showpreference(QTreeWidget* m_preferenceTreeWidget, QTreeWidgetItem* item);
    void notExpandpreference();
    void searchpreference();
    void switchOverSearchButton(bool msg);
    void showEvent(QShowEvent* event) override;
};

QT_END_NAMESPACE