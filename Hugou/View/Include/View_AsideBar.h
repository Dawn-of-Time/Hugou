#pragma once

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include "Const.h"
#include "IconTextButton.h"
#include "ButtonHoverWatcher.h"

class AsideBarView : public QWidget
{
    Q_OBJECT

public:
    AsideBarView(QWidget* parent);

signals:
    void SignalChangeStackedWidget(int index);

private:
    QVBoxLayout* m_asideBarLayout;
    QLabel* m_userLabel;
    QLabel* m_planLabel;
    IconTextButton* m_scheduleButton;
    QLabel* m_dataBaseLabel;
    IconTextButton* m_documentButton;
    IconTextButton* m_recordButton;
    IconTextButton* m_settingButton;
    ButtonHoverWatcher* m_scheduleButtonHoverWatcher;
    ButtonHoverWatcher* m_settingButtonHoverWatcher;
    QList<IconTextButton*> m_asideBarButtonList;
    const QList<QStringList> m_asideBarButtonIconList = 
    { 
        {":/icon/schedule_bla.png", ":/icon/schedule_blu.png"},
        {":/icon/setting_b.png", ":/icon/setting_w.png"}
    };

    void setupUi();
    void switchOverStackedWidget(int index);
};