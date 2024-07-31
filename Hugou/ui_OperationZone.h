#pragma once

#include <QQuickWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "Const.h"
#include "Var.h"

extern FileManager fileManager;

class Ui_OperationZone
{
public:
    QVBoxLayout* operationZoneLayout;
    QQuickWidget* operationQuickWidget;
    QLabel* operationZoneLabel;

	void setupUi(QWidget* operationZone)
	{
        operationZone->setMinimumHeight(270);
        operationZoneLayout = new QVBoxLayout(operationZone);
        operationZoneLayout->setSpacing(5);
        operationZoneLayout->setContentsMargins(10, 10, 10, 30);
        operationQuickWidget = new QQuickWidget(operationZone);
        operationQuickWidget->setObjectName("operationQuickWidget");
        operationQuickWidget->setFixedSize(320, 180);
        operationQuickWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
        operationQuickWidget->setSource(QUrl("res/qml/operationZoneMedia.qml"));
        operationQuickWidget->show();

        operationZoneLabel = new QLabel(operationZone);
        operationZoneLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        operationZoneLabel->setFont(title2);
        operationZoneLabel->setText(operationText);
        operationZoneLabel->setAlignment(Qt::AlignCenter);

        operationZoneLayout->addWidget(operationQuickWidget, 0, Qt::AlignCenter);
        operationZoneLayout->addWidget(operationZoneLabel, 0, Qt::AlignCenter);

	}
};