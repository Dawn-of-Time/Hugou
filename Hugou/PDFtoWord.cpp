#include "PDFtoWord.h"

PDFtoWord::PDFtoWord(QString fileName) : 
	QWidget()
{
	pdfFileName = fileName;
	readPDFFile();
}

PDFtoWord::~PDFtoWord()
{}

// 1.文件读取（转为图片格式）
void PDFtoWord::readPDFFile()
{
	pdf->load(pdfFileName);
	pageCount = pdf->pageCount();
	qDebug() << pdf->getAllText(1).text();
}
// 2.图片预处理

// 3.OCR文字识别

// 4.文档排版

// 5.文件导出