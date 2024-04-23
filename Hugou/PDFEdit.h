#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QPDFWriter>
#include <QtPdf/QPDFDocument>
#include <QPainter>
#include <QPrinter>
#include "Const.h"
#include "ButtonHoverWatcher.h"

class PDFEdit
	:public QWidget
{
public:
    QString pdfFileName;
    QPdfWriter* writer;
    QPdfDocument* pdf = new QPdfDocument();
    int pageCount = 0;
    QFrame* centralFrame;
    QLabel* dragZone;
    QPushButton* helpButton;
    QPushButton* minimizeButton;
    QPushButton* islandButton;
    QPushButton* closeButton;
    ButtonHoverWatcher* closeButtonHoverWatcher;
    ButtonHoverWatcher* islandButtonHoverWatcher;
	PDFEdit(QString fileName);
    void readPDFFile();
    void removePage(int page);
};

