#include "Controller_Settings.h"

SettingsController::SettingsController(SettingsView* settingsView, SettingsModel* settingsModel)
    : QObject(), m_settingsView(settingsView), m_settingsModel(settingsModel)
{
    connect(m_settingsView->m_searchLineEdit, &QLineEdit::textChanged, m_settingsView, &SettingsView::checkIsLineEditNull);
    connect(m_settingsView->m_searchButton, &QPushButton::clicked, m_settingsView, &SettingsView::searchSettings);
    connect(m_settingsView->m_settingsTreeWidget, &QTreeWidget::itemClicked, this, &SettingsController::settingsTreeItemExpandOrCollapseRequest);
    connect(m_settingsView->m_settingsTreeWidget, &QTreeWidget::itemDoubleClicked, this, &SettingsController::settingsContentListWidgetSrollRequest);
    connect(settingsComboboxMap["themeBox"], &QComboBox::currentTextChanged, this, &SettingsController::applyThemeRequest);
}

void SettingsController::settingsTreeItemExpandOrCollapseRequest(QTreeWidgetItem* item, int column)
{
    item->setExpanded(!item->isExpanded());
}

void SettingsController::settingsContentListWidgetSrollRequest(QTreeWidgetItem* item, int column)
{
    int row = settingsItemRowMap[item->text(column)];
    m_settingsView->m_settingsContentListWidget->scrollToItem(m_settingsView->m_settingsContentListWidget->item(row), QAbstractItemView::PositionAtTop);
}

void SettingsController::applyThemeRequest(QString theme)
{
    if (m_userChanged) emit SignalApplyTheme(theme);
}