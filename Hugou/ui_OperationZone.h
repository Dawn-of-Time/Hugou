#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QLabel>
#include <QMediaPlayer>
#include <QTableWidget>
#include <QHeaderView>
#include "Const.h"
#include "Var.h"

extern FileManager fileManager;

class Ui_OperationZone
{
public:
    QVBoxLayout* operationZoneLayout;
    QWidget* operationZoneIllustrator;
    QVideoWidget* operationVideoWidget;
    QHBoxLayout* videoWidgetLayout;
    QLabel* operationZoneLabel;
    QMediaPlayer* player;

	void setupUi(QWidget* operationZone)
	{
        operationZone->setMaximumHeight(270);
        operationZoneLayout = new QVBoxLayout(operationZone);
        operationZoneLayout->setSpacing(5);
        operationZoneLayout->setContentsMargins(10, 10, 10, 30);
        operationZoneIllustrator = new QWidget(operationZone);
        operationZoneIllustrator->setFixedHeight(200);
        operationZoneIllustrator->setAttribute(Qt::WA_TransparentForMouseEvents);
        operationVideoWidget = new QVideoWidget(operationZoneIllustrator);
        operationVideoWidget->setObjectName("operationVideoWidget");
        QPalette palette;
        palette.setColor(QPalette::Window, Qt::white);
        operationVideoWidget->setAutoFillBackground(true);
        operationVideoWidget->setPalette(palette);
        operationVideoWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        operationVideoWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
        // Ë«»º³å
        //operationVideoWidget->setAttribute(Qt::WA_PaintOnScreen, false);
        //operationVideoWidget->setAttribute(Qt::WA_NoSystemBackground, true);
        //operationVideoWidget->setAttribute(Qt::WA_OpaquePaintEvent, true);
        //operationVideoWidget->setAttribute(Qt::WA_StaticContents, true);
        videoWidgetLayout = new QHBoxLayout(operationZoneIllustrator);
        videoWidgetLayout->setContentsMargins(0, 0, 0, 0);
        videoWidgetLayout->setSpacing(0);
        //videoWidgetLayout->setAlignment(Qt::AlignCenter);
        videoWidgetLayout->addWidget(operationVideoWidget, Qt::AlignCenter);
        player = new QMediaPlayer(operationVideoWidget);
        player->setSource(QUrl::fromLocalFile("res/mp4/dropZone.mp4"));
        player->setVideoOutput(operationVideoWidget);
        player->setLoops(-1);
        player->play();
        operationZoneLabel = new QLabel(operationZone);
        operationZoneLabel->setFixedSize(600, 30);
        operationZoneLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        operationZoneLabel->setFont(title2);
        operationZoneLabel->setText(operationText);
        operationZoneLabel->setAlignment(Qt::AlignHCenter);
        operationZoneLayout->addStretch();
        operationZoneLayout->addWidget(operationZoneIllustrator, Qt::AlignHCenter);
        operationZoneLayout->addWidget(operationZoneLabel, Qt::AlignHCenter);
        operationZoneLayout->addStretch();

        operationVideoWidget->resize(320, 180);

	}
};