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
    QFrame* m_asideFrame;
    QVBoxLayout* m_asideFrameLayout;
    QLabel* m_userLabel;
    IconTextButton* m_workSpaceButton;
    IconTextButton* m_settingButton;
    ButtonHoverWatcher* m_workSpaceButtonHoverWatcher;
    ButtonHoverWatcher* m_settingButtonHoverWatcher;
    QList<IconTextButton*> m_asideBarButtonList;
    const QList<QStringList> m_asideBarButtonIconList = 
    { 
        {":/icon/workSpace_w.png", ":/icon/workSpace_b.png"},
        {":/icon/setting_w.png", ":/icon/setting_b.png"}
    };

    void setupUi();
    void showEvent(QShowEvent* event) override;
    void switchOverStackedWidget(int index);
};