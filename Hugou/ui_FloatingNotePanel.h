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
        floatingNotePanel->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight - titleFrameHeight);
        floatingNotePanel->setFont(QFont("Hind", 30));
        floatingNotePanel->setAlignment(Qt::AlignCenter);
        floatingNotePanel->setHidden(true);

        // 样式表设置
        QFile styleFile("res/theme/Global/floatingNotePanel.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        floatingNotePanel->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
};