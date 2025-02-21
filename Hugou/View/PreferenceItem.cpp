#include "PreferenceItem.h"

void LabelTitleItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(this->level, ItemType::LabelTitleType)];
    QLabel* label = new QLabel(this->text, preferenceContentListWidget);
    label->setStyleSheet(style.first);
    label->setFont(style.second);
    PreferenceItem->setSizeHint(QSize(label->sizeHint().width(), label->sizeHint().height() - 10));
    preferenceContentListWidget->setItemWidget(PreferenceItem, label);
    PreferenceMap.preferenceItemRowMap.insert(this->text, preferenceContentListWidget->indexFromItem(PreferenceItem).row());
}

void LabelHintItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Hint, ItemType::LabelHintType)];
    QWidget* widget = new QWidget(preferenceContentListWidget);
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
    PreferenceItem->setSizeHint(widget->size());
    preferenceContentListWidget->setItemWidget(PreferenceItem, widget);
    PreferenceMap.hintItemLabelMap.insert(PreferenceItem, label);
}

void ChapterSpaceItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QLabel* space = new QLabel(preferenceContentListWidget);
    PreferenceItem->setSizeHint(QSize(preferenceContentListWidget->width(), 40));
    preferenceContentListWidget->setItemWidget(PreferenceItem, space);
}

void SectionSpaceItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QLabel* space = new QLabel(preferenceContentListWidget);
    PreferenceItem->setSizeHint(QSize(preferenceContentListWidget->width(), 20));
    preferenceContentListWidget->setItemWidget(PreferenceItem, space);
}

void ComboboxItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::ComboboxType)];
    QLabel* label = new QLabel(preferenceContentListWidget);
    label->setStyleSheet(style.first);
    QComboBox* comboBox = new QComboBox(label);
    QString value;
    PreferenceHelper::getHelper()->getpreferenceValue(m_name, value);
    comboBox->setObjectName(this->m_name);
    comboBox->move(20, 0);
    if (this->m_list.isEmpty()) comboBox->addItems({ "(No options)" });
    else comboBox->addItems(this->m_list);
    comboBox->setCurrentText(value);
    comboBox->setFont(style.second);
    comboBox->setFixedSize(300, 30);
    ComboboxWheelWatcher* comboBoxWheelWatcher = new ComboboxWheelWatcher(comboBox);
    comboBox->installEventFilter(comboBoxWheelWatcher);
    PreferenceItem->setSizeHint(QSize(preferenceContentListWidget->width(), 30));
    preferenceContentListWidget->setItemWidget(PreferenceItem, label);
    PreferenceMap.preferenceComboboxMap.insert(m_name, comboBox);
}

void LineEditItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::LineEditType)];
    QString value;
    PreferenceHelper::getHelper()->getpreferenceValue(m_name, value);
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
    PreferenceItem->setSizeHint(QSize(preferenceContentListWidget->width(), 30));
    preferenceContentListWidget->setItemWidget(PreferenceItem, lineEdit);
    PreferenceMap.preferenceLineEditMap.insert(m_name, lineEdit);
}

void LineEditWithTrailingButtonItem::generatePreferenceItem(QListWidget* preferenceContentListWidget, PreferenceMap& PreferenceMap)
{
    QListWidgetItem* PreferenceItem = new QListWidgetItem(preferenceContentListWidget);
    QPair<QString, QFont> style = itemStyleMap[qMakePair(Level::Content, ItemType::LineEditWithTrailingButtonType)];
    QLabel* label = new QLabel(preferenceContentListWidget);
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

    PreferenceItem->setSizeHint(QSize(preferenceContentListWidget->width(), 30));
    preferenceContentListWidget->setItemWidget(PreferenceItem, label);
}