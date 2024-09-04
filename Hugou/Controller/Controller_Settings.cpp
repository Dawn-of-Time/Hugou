#include "Controller_Settings.h"

SettingsController::SettingsController(SettingsView* settingsView, SettingsModel* settingsModel)
    : QObject(), m_settingsView(settingsView), m_settingsModel(settingsModel)
{
    connect(settingsView->m_searchLineEdit, &QLineEdit::textChanged, settingsView, &SettingsView::checkIsLineEditNull);
    connect(settingsView->m_searchButton, &QPushButton::clicked, settingsView, &SettingsView::searchSettings);
    connect(settingsView->m_settingsTreeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem* item, int column) {item->setExpanded(!item->isExpanded()); });
    connect(settingsView->m_settingsTreeWidget, &QTreeWidget::itemDoubleClicked, [&](QTreeWidgetItem* item, int column)
        {
            int row = settingsItemRowMap[item->text(column)];
            settingsView->m_settingsContentListWidget->scrollToItem(settingsView->m_settingsContentListWidget->item(row), QAbstractItemView::PositionAtTop);
        });
    connect(settingsComboboxMap["themeBox"], &QComboBox::currentIndexChanged, [&](int index)
        {
            SettingsHelper* helper = SettingsHelper::getHelper();
            helper->writeSettings("theme", settingsComboboxMap["themeBox"]->currentText());
            emit SignalApplyTheme(settingsComboboxMap["themeBox"]->currentText());
        });
}