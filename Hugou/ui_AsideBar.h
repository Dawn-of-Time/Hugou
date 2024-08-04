#pragma once

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include "Const.h"
#include "IconTextButton.h"
#include "ButtonHoverWatcher.h"

class Ui_AsideBar
{
public:
    QFrame* asideFrame;
    QVBoxLayout* asideFrameLayout;
    QLabel* userLabel;
    IconTextButton* workSpaceButton;
    IconTextButton* settingButton;
    ButtonHoverWatcher* workSpaceButtonHoverWatcher;
    ButtonHoverWatcher* settingButtonHoverWatcher;

    void setupUi(QWidget* asideBar)
    {
        asideBar->setFixedWidth(asideFrameWidth);
        asideBar->setMinimumHeight(asideFrameHeight);
        asideFrame = new QFrame(asideBar);
        asideFrame->setObjectName("asideFrame");
        asideFrameLayout = new QVBoxLayout(asideFrame);
        asideFrameLayout->setContentsMargins(5, 0, 5, 0);
        asideFrameLayout->setSpacing(5);
        userLabel = new QLabel(asideBar);
        userLabel->setObjectName("userLabel");
        userLabel->setFixedSize(userLabelWidth, userLabelHeight);
        workSpaceButton = new IconTextButton(QPixmap("res/ico/workSpace_b.png"), "WorkSpace", asideFont, asideBar);
        workSpaceButton->setObjectName("workSpaceButton");
        workSpaceButton->setFixedSize(asideButtonWidth, asideButtonHeight);
        workSpaceButton->setEnabled(false);
        settingButton = new IconTextButton(QPixmap("res/ico/setting_w.png"), "Settings", asideFont, asideBar);
        settingButton->setObjectName("settingButton");
        settingButton->setFixedSize(asideButtonWidth, asideButtonHeight);
        asideFrameLayout->addWidget(userLabel, Qt::AlignLeft);
        asideFrameLayout->addWidget(workSpaceButton, Qt::AlignLeft);
        asideFrameLayout->addWidget(settingButton, Qt::AlignLeft);
        asideFrameLayout->addStretch();

        workSpaceButton->setProperty("status", "current");
        settingButton->setProperty("status", "default");
    }
};