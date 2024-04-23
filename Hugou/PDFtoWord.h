#pragma once

#include <QtPdf\qpdfdocument.h>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE

class PDFtoWord :
	public QWidget
{
public:
	PDFtoWord(QString fileName);
	~PDFtoWord();

	QString pdfFileName;
	QPdfDocument* pdf = new QPdfDocument();
	int pageCount = 0;
	// 1.文件读取（转为图片格式）
	void readPDFFile();
	// 2.图片预处理

	// 3.OCR文字识别

	// 4.文档排版

	// 5.文件导出
};

QT_END_NAMESPACE