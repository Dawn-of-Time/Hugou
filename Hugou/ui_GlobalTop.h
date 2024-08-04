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
        globalTopLayout->setSpacing(30);
        globalTopQuickWidget = new QQuickWidget(globalTop);
        globalTopQuickWidget->setObjectName("globalTopQuickWidget");
        globalTopQuickWidget->setFixedSize(240, 240);
        QSizePolicy globalTopQuickWidgetSizePolicy = globalTopQuickWidget->sizePolicy();
        globalTopQuickWidgetSizePolicy.setRetainSizeWhenHidden(true);
        globalTopQuickWidget->setSizePolicy(globalTopQuickWidgetSizePolicy);

        globalTopHint = new QLabel(globalTop);
        globalTopHint->setFont(hintFont);
        globalTopHint->setAlignment(Qt::AlignCenter);
        QSizePolicy globalTopHintSizePolicy = globalTopHint->sizePolicy();
        globalTopHintSizePolicy.setRetainSizeWhenHidden(true);
        globalTopHint->setSizePolicy(globalTopHintSizePolicy);

        globalTopLayout->addStretch(1);
        globalTopLayout->addWidget(globalTopQuickWidget, 0, Qt::AlignHCenter);
        globalTopLayout->addWidget(globalTopHint, 0, Qt::AlignHCenter);
        globalTopLayout->addStretch(1);

        globalTop->setHidden(true);
    }
};