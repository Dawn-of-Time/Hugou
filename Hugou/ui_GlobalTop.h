#pragma once
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include <QQuickWidget>
#include "Const.h"

class Ui_GlobalTop
{
public:
    QVBoxLayout* globalTopLayout;
    QQuickWidget* globalTopQuickWidget;
    QLabel* globalTopHint;

    void setupUi(QWidget* globalTop)
    {
        globalTop->setObjectName("globalTop");
        globalTop->setGeometry(0, 0, mainWindowWidth, mainWindowHeight);
        globalTopLayout = new QVBoxLayout(globalTop);
        globalTopLayout->setSpacing(10);
        globalTopQuickWidget = new QQuickWidget(globalTop);
        globalTopQuickWidget->setObjectName("globalTopQuickWidget");
        globalTopQuickWidget->setFixedSize(240, 240);
        globalTopHint = new QLabel(globalTop);
        globalTopHint->setFont(hintFont);
        globalTopHint->setAlignment(Qt::AlignCenter);

        globalTopLayout->addStretch(1);
        globalTopLayout->addWidget(globalTopQuickWidget, 0, Qt::AlignHCenter);
        globalTopLayout->addWidget(globalTopHint, 0, Qt::AlignHCenter);
        globalTopLayout->addStretch(1);

        globalTop->setHidden(true);

        // 样式表设置
        //QFile styleFile("res/theme/Global/globalTop.qss");
        //styleFile.open(QIODeviceBase::ReadOnly);
        //globalTop->setStyleSheet(styleFile.readAll());
        //styleFile.close();
    }
};