#include "WorkSpace.h"

WorkSpace::WorkSpace(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    QTime currentTime = QTime::currentTime();
    if (currentTime.hour() >= 0 && currentTime.hour() < 12) { ui.workSpaceLabel->setText("Good Morning!"); }
    else if (currentTime.hour() >= 12 && currentTime.hour() < 18) { ui.workSpaceLabel->setText("Good Afternoon!"); }
    else { ui.workSpaceLabel->setText("Good Evening!"); }

    connect(ui.operationZone, &OperationZone::signalAdd, this, &WorkSpace::slotAdd);
}

void WorkSpace::slotAdd(QString filePath)
{
    ui.recentlyAddedZoneLabel->setHidden(true);
    ui.addTable->setHidden(false);
    File file(filePath);
    QLabel* fileInfo = file.formItem(ui.addTable);
    QLabel* statusLabel = new QLabel(ui.addTable);
    QPixmap pm(":/icon/success_status");
    pm = pm.scaled(QSize(20, 20), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    statusLabel->setPixmap(pm);
    statusLabel->setAlignment(Qt::AlignCenter);
    ui.addTable->insertRow(ui.addTable->rowCount());
    ui.addTable->setCellWidget(ui.addTable->rowCount() - 1, 0, fileInfo);
    ui.addTable->setCellWidget(ui.addTable->rowCount() - 1, 1, statusLabel);
    ui.addTable->setRowHeight(ui.addTable->rowCount() - 1, 60);
}