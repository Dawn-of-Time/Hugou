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
#include "Assistance_SettingsHelper.h"
#include "SettingItem.h"
#include "Const_Text.h"

QT_BEGIN_NAMESPACE

class SettingsController;

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView(QWidget* parent);
    ~SettingsView();
    void adjustSizeHint();

protected slots:
    void checkIsLineEditNull();
    void deleteSearchText();

private:
    const QString searchText = QString(tr("Search item."));
    friend class SettingsController;
    QHBoxLayout* m_settingsLayout;
    QWidget* m_settingsLeftWidget;
    QVBoxLayout* m_settingsLeftLayout;
    QLineEdit* m_searchLineEdit;
    QPushButton* m_searchButton;
    QPushButton* m_searchDeletedButton;
    ButtonHoverWatcher* m_searchButtonHoverWatcher;
    ButtonHoverWatcher* m_searchDeletedButtonHoverWatcher;
    QStackedWidget* m_settingsTreeStackedWidget;
    QVBoxLayout* m_settingsTreeLayout;
    QTreeWidget* m_settingsTreeWidget;
    QLabel* m_searchsettingsNullLabel;
    QWidget* m_settingsRightWidget;
    QVBoxLayout* m_settingsRightLayout;
    QListWidget* m_settingsContentListWidget;
    SettingItem::SettingMap m_settingMap;
    const QList<SettingItem*> m_settingsItemList =
    {
        new LabelTitleItem("Common", SettingItem::Level::First),
        new LabelTitleItem("Appearance", SettingItem::Level::Second),
        new LabelTitleItem("Theme", SettingItem::Level::Third),
        new ComboboxItem("theme", settingsValueMap["theme"]),
        new LabelHintItem("I will be launching the theme preview feature in the near future."),
        new SectionSpaceItem(),
        new LabelTitleItem("Country/Region", SettingItem::Level::Second),
        new LabelTitleItem("Language", SettingItem::Level::Third),
        new ComboboxItem("language", settingsValueMap["language"]),
        new LabelHintItem("More and more languages are getting support. The language currently in the pipeline is: Chinese."),
        new ChapterSpaceItem(),

        new LabelTitleItem("Task", SettingItem::Level::First),
        new LabelTitleItem("Recycle Bin", SettingItem::Level::Second),
        new LabelTitleItem("Enable", SettingItem::Level::Third),
        new ComboboxItem("recycleBin", settingsValueMap["recycleBin"]),
        new LabelHintItem("Enable this feature: When you delete a task, it will be moved to the recycle bin and completely destroyed after retention period."),
        new LabelTitleItem("Retention Period", SettingItem::Level::Third),
        new LineEditItem("retentionPeriod", new QIntValidator(1, 30)),
        new LabelHintItem("Set the number of days you expect to retain. Limit it to 1-30."),
        new ChapterSpaceItem()
    };

    void setupUi();
    void formTree();
    void formContentList();
    void showSettings(QTreeWidget* m_settingsTreeWidget, QTreeWidgetItem* item);
    void notExpandSettings();
    void searchSettings();
    void switchOverSearchButton(bool msg);
    void showEvent(QShowEvent* event) override;
};

QT_END_NAMESPACE