#pragma once

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>
#include <QWidgetAction>
#include <QFile>
#include <math.h>
#include <QTextLayout>
#include "ButtonHoverWatcher.h"
#include "SettingsHelper.h"
#include "Const_Text.h"

QT_BEGIN_NAMESPACE

inline QMap<QString, int> settingsItemRowMap;
inline QMap<QString, QComboBox*> settingsComboboxMap;
inline QMap<QListWidgetItem*, QLabel*> hintItemLabelMap;

class SettingsController;

class SettingItem
{
public:
    enum class Level { First, Second, Third, Content, Hint, Spacer };
    enum class ItemType
    {
        LabelTitleType, LabelHintType,
        SectionSpaceType, ChapterSpaceType,
        ComboboxType, LineEditWithTrailingButtonType
    };
    const QMap<QPair<Level, ItemType>, QPair<QString, QFont>> itemStyleMap =
    {
        {qMakePair(Level::First, ItemType::LabelTitleType), qMakePair("QLabel {border-width: 0 0 0 5px; border-style: solid; border-color: black; padding-left: 2px}", QFont("Hind", 22))},
        {qMakePair(Level::Second, ItemType::LabelTitleType), qMakePair("QLabel {margin-left: 15px; margin-top: 5px; margin-bottom:5px}", QFont("Hind Siliguri", 16))},
        {qMakePair(Level::Third, ItemType::LabelTitleType), qMakePair("QLabel {margin-left: 20px; margin-top: 5px; margin-bottom:5px;}", QFont("Hind Siliguri Light", 14))},
        {qMakePair(Level::Hint, ItemType::LabelHintType), qMakePair("QLabel {color: #696969; background-color: transparent}", QFont("Hind Siliguri Light", 12))},
        {qMakePair(Level::Content, ItemType::ComboboxType), qMakePair("QLabel {margin-left: 20px}", QFont("Hind Siliguri Light", 12))},
        {qMakePair(Level::Content, ItemType::LineEditWithTrailingButtonType), qMakePair("QLabel {margin-left: 20px}", QFont("Hind Siliguri Light", 12))}
    };
    const QMap<QString, QStringList> buttonIconMap =
    {
        {"savePathButton", {":/icon/browse_bla.png", ":/icon/browse_blu.png"}}
    };

    ItemType itemType;
    SettingItem() { itemType = ItemType::LabelTitleType; };
    virtual void generateSettingItem(QListWidget* settingsContentListWidget) {};
};

class LabelTitleItem : public SettingItem
{
public:
    QString text;
    Level level;
    LabelTitleItem(QString text, Level level)
        : text(text), level(level) { itemType = ItemType::LabelTitleType; };
    void generateSettingItem(QListWidget* settingsContentListWidget)
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QPair<QString, QFont> style = itemStyleMap[qMakePair(this->level, ItemType::LabelTitleType)];
        QLabel* label = new QLabel(this->text, settingsContentListWidget);
        label->setStyleSheet(style.first);
        label->setFont(style.second);
        settingItem->setSizeHint(QSize(label->sizeHint().width(), label->sizeHint().height() - 10));
        settingsContentListWidget->setItemWidget(settingItem, label);
        settingsItemRowMap.insert(this->text, settingsContentListWidget->indexFromItem(settingItem).row());
    }
};

class LabelHintItem : public SettingItem
{
public:
    QString content;
    LabelHintItem(QString content) : content(content) { itemType = ItemType::LabelHintType; };
    void generateSettingItem(QListWidget* settingsContentListWidget) override
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Hint, ItemType::LabelHintType)];
        QWidget* widget = new QWidget(settingsContentListWidget);
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->setSpacing(0);
        layout->setContentsMargins(25, 0, 0, 0);
        QLabel* label = new QLabel(this->content, widget);
        label->setStyleSheet(style.first);
        label->setFont(style.second);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignTop);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        layout->addWidget(label);
        settingItem->setSizeHint(widget->size());
        settingsContentListWidget->setItemWidget(settingItem, widget);
        hintItemLabelMap.insert(settingItem, label);
    }
};

class ChapterSpaceItem : public SettingItem
{
public:
    ChapterSpaceItem() { itemType = ItemType::ChapterSpaceType; };
    void generateSettingItem(QListWidget* settingsContentListWidget) override
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QLabel* space = new QLabel(settingsContentListWidget);
        settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 40));
        settingsContentListWidget->setItemWidget(settingItem, space);
    }
};

class SectionSpaceItem : public SettingItem
{
public:
    SectionSpaceItem() { itemType = ItemType::SectionSpaceType; };
    void generateSettingItem(QListWidget* settingsContentListWidget) override
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QLabel* space = new QLabel(settingsContentListWidget);
        settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 20));
        settingsContentListWidget->setItemWidget(settingItem, space);
    }
};

class ComboboxItem : public SettingItem
{
public:
    QString name;
    QStringList list;
    ComboboxItem(QString name, QStringList list)
        : name(name), list(list) { itemType = ItemType::ComboboxType; };
    void generateSettingItem(QListWidget* settingsContentListWidget) override
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::ComboboxType)];
        QLabel* label = new QLabel(settingsContentListWidget);
        label->setStyleSheet(style.first);
        QComboBox* comboBox = new QComboBox(label);
        comboBox->setObjectName(this->name);
        comboBox->move(20, 0);
        if (this->list.isEmpty()) comboBox->addItems({ "(No options)" });
        else comboBox->addItems(this->list);
        comboBox->setFont(style.second);
        comboBox->setFixedSize(300, 30);
        //ComboboxWheelWatcher* comboBoxWheelWatcher = new ComboboxWheelWatcher(item->listWidget());
        //comboBox->installEventFilter(comboBoxWheelWatcher);
        settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 30));
        settingsContentListWidget->setItemWidget(settingItem, label);
        settingsComboboxMap.insert(name, comboBox);
    }
};

class LineEditWithTrailingButtonItem : public SettingItem
{
public:
    QPushButton* button;
    QString buttonName;
    LineEditWithTrailingButtonItem(QPushButton* button, QString buttonName)
        : button(button), buttonName(buttonName) {itemType = ItemType::LineEditWithTrailingButtonType;};
    void generateSettingItem(QListWidget* settingsContentListWidget) override
    {
        QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
        QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::LineEditWithTrailingButtonType)];
        QLabel* label = new QLabel(settingsContentListWidget);
        label->setStyleSheet(style.first);
        QLineEdit* lineEdit = new QLineEdit(label);
        lineEdit->move(20, 0);
        lineEdit->setFont(style.second);
        lineEdit->setFixedHeight(30);
        button = new QPushButton(label);
        button->setIcon(QIcon(buttonIconMap[buttonName][0]));
        button->setCursor(Qt::ArrowCursor);
        QWidgetAction* savePathAction = new QWidgetAction(lineEdit);
        savePathAction->setDefaultWidget(button);
        lineEdit->addAction(savePathAction, QLineEdit::TrailingPosition);
        ButtonHoverWatcher* savePathButtonHoverWatcher = new ButtonHoverWatcher(buttonIconMap[buttonName][0], buttonIconMap[buttonName][1]);
        button->installEventFilter(savePathButtonHoverWatcher);

        settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 30));
        settingsContentListWidget->setItemWidget(settingItem, label);
    }
};

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView(QWidget* parent);
    void adjustSizeHint();

protected slots:
    void checkIsLineEditNull();
    void deleteSearchText();

private:
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
    QPushButton* m_savePathButton;
    QLineEdit* m_savePathLineEdit;
    const QList<SettingItem*> settingsItemList =
    {
        new LabelTitleItem("Common", SettingItem::Level::First),
        new LabelTitleItem("Appearance", SettingItem::Level::Second),
        new LabelTitleItem("Theme", SettingItem::Level::Third),
        new LabelHintItem("I will be launching the theme preview feature in the near future."),
        new ComboboxItem("themeBox", settingsValueMap["theme"]),
        new SectionSpaceItem(),
        new LabelTitleItem("Country/Region", SettingItem::Level::Second),
        new LabelTitleItem("Language", SettingItem::Level::Third),
        new LabelHintItem("More and more languages are getting support. The language currently in the pipeline is: Chinese."),
        new ComboboxItem("languageBox", settingsValueMap["language"]),
        new ChapterSpaceItem(),

        new LabelTitleItem("Export", SettingItem::Level::First),
        new LabelTitleItem("Save", SettingItem::Level::Second),
        new LabelTitleItem("Default Save Path", SettingItem::Level::Third),
        new LabelHintItem("This feature is to be developed."),
        new LineEditWithTrailingButtonItem(m_savePathButton, "savePathButton"),
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