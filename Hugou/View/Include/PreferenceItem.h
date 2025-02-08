#pragma once
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidgetAction>
#include <QComboBox>
#include <QValidator>
#include "ButtonHoverWatcher.h"
#include "Assistance_preferenceHelper.h"
#include "Assistance_ComboboxWheelWatcher.h"

class PreferenceItem
{
public:
    enum class Level { First, Second, Third, Content, Hint, Spacer };
    enum class ItemType
    {
        LabelTitleType, LabelHintType,
        SectionSpaceType, ChapterSpaceType,
        ComboboxType, LineEditType, 
        LineEditWithTrailingButtonType
    };
    struct PreferenceMap
    {
        QMap<QString, int> preferenceItemRowMap;
        QMap<QListWidgetItem*, QLabel*> hintItemLabelMap;
        QMap<QString, QComboBox*> preferenceComboboxMap;
        QMap<QString, QLineEdit*> preferenceLineEditMap;
    };

    const QMap<QPair<Level, ItemType>, QPair<QString, QFont>> itemStyleMap =
    {
        {qMakePair(Level::First, ItemType::LabelTitleType), qMakePair("QLabel {border-width: 0 0 0 5px; border-style: solid; border-color: black; padding-left: 2px}", QFont("Hind Siliguri", 22, QFont::Bold))},
        {qMakePair(Level::Second, ItemType::LabelTitleType), qMakePair("QLabel {margin-left: 15px; margin-top: 5px; margin-bottom:5px}", QFont("Hind Siliguri", 16))},
        {qMakePair(Level::Third, ItemType::LabelTitleType), qMakePair("QLabel {margin-left: 20px; margin-top: 5px; margin-bottom:5px;}", QFont("Hind Siliguri", 14, QFont::Light))},
        {qMakePair(Level::Hint, ItemType::LabelHintType), qMakePair("QLabel {color: #696969; background-color: transparent}", QFont("Hind Siliguri", 12, QFont::Light))},
        {qMakePair(Level::Content, ItemType::ComboboxType), qMakePair("QLabel {margin-left: 20px}", QFont("Hind Siliguri", 12, QFont::Light))},
        {qMakePair(Level::Content, ItemType::LineEditType), qMakePair("QLineEdit {margin-left: 20px}", QFont("Hind Siliguri", 12, QFont::Light))}, 
        {qMakePair(Level::Content, ItemType::LineEditWithTrailingButtonType), qMakePair("QLabel {margin-left: 20px}", QFont("Hind Siliguri", 12, QFont::Light))}
    };
    const QMap<QString, QStringList> buttonIconMap =
    {
       
    };

    ItemType itemType;
    PreferenceItem() { itemType = ItemType::LabelTitleType; };
    
    void virtual generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) {};
};

class LabelTitleItem : public PreferenceItem
{
public:
    QString text;
    Level level;
    LabelTitleItem(QString text, Level level)
        : text(text), level(level) {
        itemType = ItemType::LabelTitleType;
    };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class LabelHintItem : public PreferenceItem
{
public:
    QString content;
    LabelHintItem(QString content) : content(content) { itemType = ItemType::LabelHintType; };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class ChapterSpaceItem : public PreferenceItem
{
public:
    ChapterSpaceItem() { itemType = ItemType::ChapterSpaceType; };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class SectionSpaceItem : public PreferenceItem
{
public:
    SectionSpaceItem() { itemType = ItemType::SectionSpaceType; };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class ComboboxItem : public PreferenceItem
{
public:
    QString m_name;
    QStringList m_list;
    ComboboxItem(QString name, QStringList list)
        : m_name(name), m_list(list) {
        itemType = ItemType::ComboboxType;
    };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class LineEditItem : public PreferenceItem
{
public:
    QString m_name;
    QValidator* m_validator;
    LineEditItem(QString name, QValidator* validator = nullptr) 
        : m_name(name), m_validator(validator){
        itemType = ItemType::LineEditType;
    };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};

class LineEditWithTrailingButtonItem : public PreferenceItem
{
public:
    QPushButton* button;
    QString buttonName;
    LineEditWithTrailingButtonItem(QPushButton* button, QString buttonName)
        : button(button), buttonName(buttonName) {
        itemType = ItemType::LineEditWithTrailingButtonType;
    };
    void generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap) override;
};
