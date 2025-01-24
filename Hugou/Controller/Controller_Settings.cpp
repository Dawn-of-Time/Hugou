#include "Controller_Settings.h"

SettingsController::SettingsController(SettingsView* settingsView, SettingsModel* settingsModel)
    : QObject(), m_settingsView(settingsView), m_settingsModel(settingsModel)
{
    connect(m_settingsView->m_searchLineEdit, &QLineEdit::textChanged, m_settingsView, &SettingsView::checkIsLineEditNull);
    connect(m_settingsView->m_searchButton, &QPushButton::clicked, m_settingsView, &SettingsView::searchSettings);
    connect(m_settingsView->m_settingsTreeWidget, &QTreeWidget::itemClicked, this, &SettingsController::settingsTreeItemExpandOrCollapseRequest);
    connect(m_settingsView->m_settingsTreeWidget, &QTreeWidget::itemDoubleClicked, this, &SettingsController::settingsContentListWidgetSrollRequest);
    connect(m_settingsView->m_settingMap.settingsComboboxMap["theme"], &QComboBox::currentTextChanged, this, &SettingsController::applyThemeRequest);
    connect(m_settingsView->m_settingMap.settingsLineEditMap["retentionPeriod"], &QLineEdit::editingFinished, [&]()
        {
            SettingsHelper::getHelper()->setSettingsValue("retentionPeriod", m_settingsView->m_settingMap.settingsLineEditMap["retentionPeriod"]->text());
        });
    connect(m_settingsView->m_settingMap.settingsComboboxMap["recycleBin"], &QComboBox::currentTextChanged, [&](QString value)
        {
            SettingsHelper::getHelper()->setSettingsValue("recycleBin", value);
            if (value == "on") 
                m_settingsView->m_settingMap.settingsLineEditMap["retentionPeriod"]->setEnabled(true);
            else
                m_settingsView->m_settingMap.settingsLineEditMap["retentionPeriod"]->setEnabled(false);
        });
}

void SettingsController::updateThemeComboboxValue(QString value)
{
    m_settingsView->m_settingMap.settingsComboboxMap["themeBox"]->blockSignals(true);
    m_settingsView->m_settingMap.settingsComboboxMap["themeBox"]->setCurrentText(value);
    m_settingsView->m_settingMap.settingsComboboxMap["themeBox"]->blockSignals(false);
}


void SettingsController::settingsTreeItemExpandOrCollapseRequest(QTreeWidgetItem* item, int column)
{
    item->setExpanded(!item->isExpanded());
}

void SettingsController::settingsContentListWidgetSrollRequest(QTreeWidgetItem* item, int column)
{
    int row = m_settingsView->m_settingMap.settingsItemRowMap[item->text(column)];
    m_settingsView->m_settingsContentListWidget->scrollToItem(m_settingsView->m_settingsContentListWidget->item(row), QAbstractItemView::PositionAtTop);
}

void SettingsController::applyThemeRequest(QString theme)
{
    emit SignalApplyTheme(theme);
}

