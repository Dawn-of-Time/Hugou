#include "Controller_preference.h"

PreferenceController::PreferenceController(PreferenceView* preferenceView, PreferenceModel* preferenceModel)
    : QObject(), m_preferenceView(preferenceView), m_preferenceModel(preferenceModel)
{
    connect(m_preferenceView->m_searchLineEdit, &QLineEdit::textChanged, m_preferenceView, &PreferenceView::checkIsLineEditNull);
    connect(m_preferenceView->m_searchButton, &QPushButton::clicked, m_preferenceView, &PreferenceView::searchpreference);
    connect(m_preferenceView->m_preferenceTreeWidget, &QTreeWidget::itemClicked, this, &PreferenceController::preferenceTreeItemExpandOrCollapseRequest);
    connect(m_preferenceView->m_preferenceTreeWidget, &QTreeWidget::itemDoubleClicked, this, &PreferenceController::preferenceContentListWidgetSrollRequest);
    connect(m_preferenceView->m_preferenceMap.preferenceComboboxMap["theme"], &QComboBox::currentTextChanged, this, &PreferenceController::applyThemeRequest);
    connect(m_preferenceView->m_preferenceMap.preferenceLineEditMap["retentionPeriod"], &QLineEdit::editingFinished, [&]()
        {
            PreferenceHelper::getHelper()->setPreferenceValue("retentionPeriod", m_preferenceView->m_preferenceMap.preferenceLineEditMap["retentionPeriod"]->text());
        });
    connect(m_preferenceView->m_preferenceMap.preferenceComboboxMap["recycleBin"], &QComboBox::currentTextChanged, [&](QString value)
        {
            PreferenceHelper::getHelper()->setPreferenceValue("recycleBin", value);
            if (value == "on") 
                m_preferenceView->m_preferenceMap.preferenceLineEditMap["retentionPeriod"]->setEnabled(true);
            else
                m_preferenceView->m_preferenceMap.preferenceLineEditMap["retentionPeriod"]->setEnabled(false);
        });
}

PreferenceController::~PreferenceController()
{
	delete m_preferenceModel;
}

void PreferenceController::updateThemeComboboxValue(const QString& value)
{
    m_preferenceView->m_preferenceMap.preferenceComboboxMap["themeBox"]->blockSignals(true);
    m_preferenceView->m_preferenceMap.preferenceComboboxMap["themeBox"]->setCurrentText(value);
    m_preferenceView->m_preferenceMap.preferenceComboboxMap["themeBox"]->blockSignals(false);
}


void PreferenceController::preferenceTreeItemExpandOrCollapseRequest(QTreeWidgetItem* item, int column)
{
    item->setExpanded(!item->isExpanded());
}

void PreferenceController::preferenceContentListWidgetSrollRequest(QTreeWidgetItem* item, int column)
{
    int row = m_preferenceView->m_preferenceMap.preferenceItemRowMap[item->text(column)];
    m_preferenceView->m_preferenceContentListWidget->scrollToItem(m_preferenceView->m_preferenceContentListWidget->item(row), QAbstractItemView::PositionAtTop);
}

void PreferenceController::applyThemeRequest(const QString& theme)
{
    emit SignalApplyTheme(theme);
}

