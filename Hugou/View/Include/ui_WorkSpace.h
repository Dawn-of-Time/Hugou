#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>
#include <QFile>
#include <QTime>
#include <QHeaderView>
#include "OperationZone.h"
#include "ButtonHoverWatcher.h"
#include "Const.h"

class Ui_WorkSpace
{
public:
    QVBoxLayout* workSpaceLayout;
    QLabel* workSpaceLabel;
    OperationZone* operationZone;
    QWidget* recentlyAddedZone;
    QHBoxLayout* recentlyAddedZoneLayout;
    QLabel* recentlyAddedLabel;
    QLabel* recentlyAddedZoneLabel;
    QVBoxLayout* recentlyAddedZoneLabelLayout;
    QTableWidget* addTable;

    void setupUi(QWidget* workSpace)
    {
        workSpace->setObjectName("workSpaceWidget");
        workSpaceLayout = new QVBoxLayout(workSpace);
        workSpaceLayout->setContentsMargins(10, 0, 10, 10);
        workSpaceLayout->setSpacing(0);

        workSpaceLabel = new QLabel(workSpace); // 界面标题板块
        workSpaceLabel->setObjectName("workSpaceLabel");
        workSpaceLabel->setFixedHeight(stackedTitleHeight);
        
        workSpaceLabel->setFont(title1);
        
        // 操作域
        operationZone = new OperationZone(workSpace);
        operationZone->setObjectName("operationZone");

        // 最近添加域
        recentlyAddedZone = new QWidget(workSpace);
        recentlyAddedZone->setObjectName("recentlyAddedZone");
        recentlyAddedZoneLayout = new QHBoxLayout(recentlyAddedZone);
        recentlyAddedZoneLayout->setContentsMargins(0, 0, 0, 0);
        recentlyAddedLabel = new QLabel("Recently Added", recentlyAddedZone);
        recentlyAddedLabel->setObjectName("recentlyAddedLabel");
        recentlyAddedLabel->setFont(title2);
        recentlyAddedLabel->setFixedHeight(40);
        
        recentlyAddedZoneLabel = new QLabel("Looking forward to adding your first PDF file!");
        recentlyAddedZoneLabel->setFont(title2);
        recentlyAddedZoneLabel->setAlignment(Qt::AlignCenter);
        recentlyAddedZoneLayout->addWidget(recentlyAddedZoneLabel, Qt::AlignCenter);
        
        addTable = new QTableWidget(recentlyAddedZoneLabel);
        addTable->setFixedWidth(650);
        addTable->setColumnCount(2);
        addTable->setHorizontalHeaderLabels(QStringList({ "File", "Status" }));
        addTable->setColumnWidth(0, 650 * 8 / 10);
        addTable->horizontalHeader()->setFont(tableHeaderFont);
        addTable->verticalHeader()->setVisible(false);
        addTable->setShowGrid(false);
        addTable->setHidden(true);
        recentlyAddedZoneLayout->addWidget(addTable, Qt::AlignHCenter);
        
        workSpaceLayout->addWidget(workSpaceLabel);
        workSpaceLayout->addWidget(operationZone);
        workSpaceLayout->addWidget(recentlyAddedLabel);
        workSpaceLayout->addWidget(recentlyAddedZone);
        
        QFile styleFile(":/theme/Global/workSpace.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        workSpace->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
};