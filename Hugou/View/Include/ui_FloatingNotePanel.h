#pragma once
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include "FloatingNote.h"

class Ui_FloatingNotePanel
{
public:
    QVBoxLayout* floatingNotePanelLayout;
    QLabel* floatingNotePanelTitle;
    QWidget* floatingNotePanelTabBar;
    QHBoxLayout* floatingNotePanelTabBarLayout;
    QPushButton* allFloatingNoteButton;
    QPushButton* successFloatingNoteButton;
    QPushButton* informationFloatingNoteButton;
    QPushButton* warningFloatingNoteButton;
    QPushButton* errorFloatingNoteButton;
    QWidget* floatingNotePanelTabBarSlider;
    QWidget* floatingNoteButtonSlider;
    
    QWidget* floatingNoteContent;
    QList<QPushButton*> floatingNoteButtonList;

    void setupUi(QWidget* floatingNotePanel)
    {
        floatingNotePanel->setObjectName("floatingNotePanel");
        floatingNotePanel->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight - titleFrameHeight);
        floatingNotePanelLayout = new QVBoxLayout(floatingNotePanel);
        floatingNotePanelLayout->setSpacing(10);
        floatingNotePanelLayout->setContentsMargins(50, 50, 50, 50);
        floatingNotePanelTitle = new QLabel("Notification Center", floatingNotePanel);
        floatingNotePanelTitle->setObjectName("floatingNotePanelTitle");
        //floatingNotePanelTitle->setFixedHeight(50);
        floatingNotePanelTitle->setFont(QFont("Hind", 24));

        floatingNotePanelTabBar = new QWidget(floatingNotePanel);
        floatingNotePanelTabBar->setObjectName("floatingNotePanelTabBar");
        floatingNotePanelTabBarLayout = new QHBoxLayout(floatingNotePanelTabBar);
        floatingNotePanelTabBarLayout->setContentsMargins(0, 0, 0, 0);
        floatingNotePanelTabBarLayout->setSpacing(50);
        allFloatingNoteButton = new QPushButton("All", floatingNotePanelTabBar);
        allFloatingNoteButton->setObjectName("allFloatingNoteButton");
        allFloatingNoteButton->setFont(floatingNotePanelButtonFont);
        allFloatingNoteButton->setFixedHeight(30);
        successFloatingNoteButton = new QPushButton("Success", floatingNotePanelTabBar);
        successFloatingNoteButton->setObjectName("successFloatingNoteButton");
        successFloatingNoteButton->setFont(floatingNotePanelButtonFont);
        successFloatingNoteButton->setFixedHeight(30);
        informationFloatingNoteButton = new QPushButton("Information", floatingNotePanelTabBar);
        informationFloatingNoteButton->setObjectName("informationFloatingNoteButton");
        informationFloatingNoteButton->setFont(floatingNotePanelButtonFont);
        informationFloatingNoteButton->setFixedHeight(30);
        warningFloatingNoteButton = new QPushButton("Warning", floatingNotePanelTabBar);
        warningFloatingNoteButton->setObjectName("warningFloatingNoteButton");
        warningFloatingNoteButton->setFont(floatingNotePanelButtonFont);
        warningFloatingNoteButton->setFixedHeight(30);
        errorFloatingNoteButton = new QPushButton("Error", floatingNotePanelTabBar);
        errorFloatingNoteButton->setObjectName("errorFloatingNoteButton");
        errorFloatingNoteButton->setFont(floatingNotePanelButtonFont);
        errorFloatingNoteButton->setFixedHeight(30);
        floatingNoteButtonList = {
            allFloatingNoteButton,
            successFloatingNoteButton,
            informationFloatingNoteButton,
            warningFloatingNoteButton,
            errorFloatingNoteButton
        };

        floatingNotePanelTabBarLayout->addWidget(allFloatingNoteButton);
        floatingNotePanelTabBarLayout->addWidget(successFloatingNoteButton);
        floatingNotePanelTabBarLayout->addWidget(informationFloatingNoteButton);
        floatingNotePanelTabBarLayout->addWidget(warningFloatingNoteButton);
        floatingNotePanelTabBarLayout->addWidget(errorFloatingNoteButton);

        floatingNotePanelTabBarSlider = new QWidget(floatingNotePanel);
        floatingNotePanelTabBarSlider->setObjectName("floatingNotePanelTabBarSlider");
        floatingNotePanelTabBarSlider->setFixedHeight(6);

        floatingNoteButtonSlider = new QWidget(floatingNotePanelTabBarSlider);
        floatingNoteButtonSlider->setObjectName("floatingNoteButtonSlider");
        floatingNoteButtonSlider->setFixedHeight(6);

        floatingNoteContent = new QWidget(floatingNotePanel);
        floatingNoteContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        floatingNotePanelLayout->addWidget(floatingNotePanelTitle);
        floatingNotePanelLayout->addWidget(floatingNotePanelTabBar);
        floatingNotePanelLayout->addWidget(floatingNotePanelTabBarSlider);
        floatingNotePanelLayout->addWidget(floatingNoteContent);
        updateProperty(0);
        
        // 样式表设置
        QFile styleFile(":/theme/Global/floatingNotePanel.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        floatingNotePanel->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    void updateProperty(int buttonIndex)
    {
        floatingNoteButtonList[buttonIndex]->setProperty("status", "current");
        for (QPushButton* button : floatingNoteButtonList)
        {
            if (button == floatingNoteButtonList[buttonIndex]) continue;
            button->setProperty("status", "default");
        }
    }
};