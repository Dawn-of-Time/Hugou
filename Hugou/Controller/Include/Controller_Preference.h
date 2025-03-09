#pragma once

#include "View/Include/View_Preference.h"
#include "Model/Include/Model_Preference.h"
#include "Utils/Include/Utils_ConfigurationHelper.h"

class PreferenceController : public QObject
{

    Q_OBJECT

public:
    PreferenceController(PreferenceView* preferenceView, PreferenceModel* preferenceModel);
	~PreferenceController();
    void updateThemeComboboxValue(const QString& value);        // 通过程序修改值，不触发相关槽函数
    bool m_userChanged = true;

signals:
    void SignalApplyTheme(QString theme = "");

protected slots:
    void preferenceTreeItemExpandOrCollapseRequest(QTreeWidgetItem* item, int column);
    void preferenceContentListWidgetSrollRequest(QTreeWidgetItem* item, int column);
    void applyThemeRequest(const QString& theme);

private:
    PreferenceView* m_preferenceView;
    PreferenceModel* m_preferenceModel;
};