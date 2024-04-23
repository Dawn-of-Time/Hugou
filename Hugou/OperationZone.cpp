#include "OperationZone.h"
#include "File.h"

OperationZone::OperationZone(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	this->setAcceptDrops(true);
    connect(this, &OperationZone::clicked, this, &OperationZone::searchFromExplorer);
}

// ²Ûº¯Êý
void OperationZone::searchFromExplorer()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Choose PDF File"), "F:", QStringLiteral("(*pdf);"));
    if (!fileName.isEmpty())
    {
        emit signalAdd(fileName);
    }
}