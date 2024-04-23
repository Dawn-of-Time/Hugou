#pragma once

#include <QString>
#include <QFileInfo>
#include <QTime>
#include <QDateTime>
#include <QLabel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class File
{
public:
	enum class Status
	{
		Existed,
		Deleted
	};
	QString filePath;
	QString fileName;
	QString fileAddMonth;
	QString fileAddDay;
	Status status;

	File(QString filePath);
	QLabel* formItem(QTableWidget* tableWidget);
};

