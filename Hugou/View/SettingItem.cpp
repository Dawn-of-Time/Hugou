#include "SettingItem.h"

void LabelTitleItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
{
    QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(this->level, ItemType::LabelTitleType)];
    QLabel* label = new QLabel(this->text, settingsContentListWidget);
    label->setStyleSheet(style.first);
    label->setFont(style.second);
    settingItem->setSizeHint(QSize(label->sizeHint().width(), label->sizeHint().height() - 10));
    settingsContentListWidget->setItemWidget(settingItem, label);
    settingMap.settingsItemRowMap.insert(this->text, settingsContentListWidget->indexFromItem(settingItem).row());
}

void LabelHintItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
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
    settingMap.hintItemLabelMap.insert(settingItem, label);
}

void ChapterSpaceItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
{
    QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
    QLabel* space = new QLabel(settingsContentListWidget);
    settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 40));
    settingsContentListWidget->setItemWidget(settingItem, space);
}

void SectionSpaceItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
{
    QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
    QLabel* space = new QLabel(settingsContentListWidget);
    settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 20));
    settingsContentListWidget->setItemWidget(settingItem, space);
}

void ComboboxItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
{
    QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::ComboboxType)];
    QLabel* label = new QLabel(settingsContentListWidget);
    label->setStyleSheet(style.first);
    QComboBox* comboBox = new QComboBox(label);
    QString value;
    SettingsHelper::getHelper()->getSettingsValue(m_name, value);
    comboBox->setObjectName(this->m_name);
    comboBox->move(20, 0);
    if (this->m_list.isEmpty()) comboBox->addItems({ "(No options)" });
    else comboBox->addItems(this->m_list);
    comboBox->setCurrentText(value);
    comboBox->setFont(style.second);
    comboBox->setFixedSize(300, 30);
    ComboboxWheelWatcher* comboBoxWheelWatcher = new ComboboxWheelWatcher(comboBox);
    comboBox->installEventFilter(comboBoxWheelWatcher);
    settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 30));
    settingsContentListWidget->setItemWidget(settingItem, label);
    settingMap.settingsComboboxMap.insert(m_name, comboBox);
}

void LineEditItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
{
    QListWidgetItem* settingItem = new QListWidgetItem(settingsContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::LineEditType)];
    QString value;
    SettingsHelper::getHelper()->getSettingsValue(m_name, value);
    QLineEdit* lineEdit = new QLineEdit(value);
    lineEdit->setStyleSheet(style.first);
    lineEdit->move(20, 0);
    lineEdit->setFont(style.second);
    lineEdit->setFixedSize(300, 30);
    if (m_validator)
    {
        m_validator->setParent(lineEdit);
        lineEdit->setValidator(m_validator);
    }
    settingItem->setSizeHint(QSize(settingsContentListWidget->width(), 30));
    settingsContentListWidget->setItemWidget(settingItem, lineEdit);
    settingMap.settingsLineEditMap.insert(m_name, lineEdit);
}

void LineEditWithTrailingButtonItem::generateSettingItem(QListWidget* settingsContentListWidget, SettingMap& settingMap)
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