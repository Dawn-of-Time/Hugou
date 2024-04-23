#pragma once
#include <QLabel>
#include <QFile>
#include "Const.h"

class Ui_FloatingNotePanel
{
public:
    void setupUi(QLabel* floatingNotePanel)
    {
        floatingNotePanel->setText("TO BE DEVELOPED");
        floatingNotePanel->setObjectName("notePanel");
        floatingNotePanel->setGeometry(asideFrameWidth, titleFrameHeight, mainWindowWidth - asideFrameWidth, mainWindowHeight - titleFrameHeight);
        floatingNotePanel->setFont(QFont("Hind", 30));
        floatingNotePanel->setAlignment(Qt::AlignCenter);
        floatingNotePanel->setHidden(true);

        // 样式表设置
        QFile styleFile("res/style/Default/floatingNotePanel.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        floatingNotePanel->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
};