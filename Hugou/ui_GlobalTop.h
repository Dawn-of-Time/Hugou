#pragma once
#include <QLabel>
#include <QFile>
#include "Const.h"

class Ui_GlobalTop
{
public:
    void setupUi(QWidget* globalTop)
    {
        //globalTop->setText("TO BE DEVELOPED");
        globalTop->setObjectName("notePanel");
        globalTop->setGeometry(0, 0, mainWindowWidth, mainWindowHeight);
        //globalTop->setFont(QFont("Hind", 30));
        //globalTop->setAlignment(Qt::AlignCenter);
        globalTop->setHidden(true);

        // 样式表设置
        QFile styleFile("res/theme/Global/globalTop.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        globalTop->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
};