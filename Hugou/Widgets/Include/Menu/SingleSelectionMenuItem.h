#pragma once
#include "MenuItem.h"
#include <QButtonGroup>
#include <QRadioButton>

class SingleSelectionMenuItem :
    public MenuItem
{
    Q_OBJECT

public:
    SingleSelectionMenuItem(const QString& title, const QList<QString>& selectionList, QWidget* menu);
    //void addSelection(const QString& selection);
    QString save() override;

signals:
    void SignalSelected(QString selected);

private:
    QString m_selected = "";
    QWidget* m_centralWidget;
    QVBoxLayout* m_centralWidgetLayout;
    QButtonGroup* m_buttonGroup;
    QList<QString> m_selectionList;
    void setupUi();
};

