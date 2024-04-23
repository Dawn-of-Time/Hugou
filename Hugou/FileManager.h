#pragma once
#include "File.h"
#include <QQueue>

class FileManager
{
public:
	QQueue<File> fileQueue;
};

