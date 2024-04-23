#include "File.h"
#include "Const.h"

File::File(QString filePath)
{
	this->filePath = filePath;
	this->fileName = QFileInfo(filePath).fileName();
	this->fileAddMonth = QDateTime::currentDateTime().toString("MMMM");
	this->fileAddDay = QString::number(QDateTime::currentDateTime().date().day());
	this->status = Status::Existed;
}

QLabel* File::formItem(QTableWidget* tableWidget)
{
	QLabel* fileInfo = new QLabel(tableWidget);
	QVBoxLayout* fileInfoLayout = new QVBoxLayout(fileInfo);
	fileInfoLayout->setContentsMargins(20, 5, 5, 5);
	QLabel* fileNameLabel = new QLabel(this->fileName, fileInfo);
	fileNameLabel->setFont(tableContentFont);
	QLabel* filePathLabel = new QLabel(this->filePath, fileInfo);
	filePathLabel->setFont(tableSubcontentFont);
	QPalette palette;
	palette.setColor(QPalette::Text, QColor("#cccccc"));
	filePathLabel->setPalette(palette);
	fileInfoLayout->addWidget(fileNameLabel, 2);
	fileInfoLayout->addWidget(filePathLabel, 1);
	return fileInfo;
}