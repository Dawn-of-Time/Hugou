#include "PDFEdit.h"

PDFEdit::PDFEdit(QString fileName) :
	QWidget()
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    // ������
    centralFrame = new QFrame(this);
    centralFrame->setObjectName("centralFrame");
    centralFrame->setGeometry(QRect(0, 0, this->width(), this->height()));

    // �������ع�
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); //ȥ����������֧�ֵ���������ͼ����С��
    dragZone = new QLabel(this); // ��ק����
    dragZone->setObjectName("dragZone");
    dragZone->setGeometry(0, 0, this->width() - 5 * titleButtonWidth, titleButtonHeight);
    helpButton = new QPushButton(this); // ������ť
    helpButton->setObjectName("helpButton");
    helpButton->setIcon(QIcon("res/help_b.png"));
    helpButton->setIconSize(QSize(18, 18));
    helpButton->setGeometry(this->width() - 4 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    minimizeButton = new QPushButton(this); // ��С����ť
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setIcon(QIcon("res/minimize_b.png"));
    minimizeButton->setIconSize(QSize(18, 18));
    minimizeButton->setGeometry(this->width() - 3 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    islandButton = new QPushButton(this); // ���찴ť
    islandButton->setObjectName("islandButton");
    islandButton->setIcon(QIcon("res/island_b.png"));
    islandButton->setIconSize(QSize(18, 18));
    islandButton->setGeometry(this->width() - 2 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    islandButtonHoverWatcher = new ButtonHoverWatcher(QString("res/island_b.png"), QString("res/island_w.png"), this);
    islandButton->installEventFilter(islandButtonHoverWatcher);
    closeButton = new QPushButton(this);  // �رհ�ť
    closeButton->setObjectName("closeButton");
    closeButton->setIcon(QIcon("res/close_bla.png"));
    closeButton->setIconSize(QSize(18, 18));
    closeButton->setGeometry(titleFrameWidth - titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    closeButtonHoverWatcher = new ButtonHoverWatcher(QString("res/close_bla.png"), QString("res/close_w.png"), this);
    closeButton->installEventFilter(closeButtonHoverWatcher);

    //this->showMaximized();

    this->pdfFileName = fileName;
    QPdfWriter* writer = new QPdfWriter(fileName);
    readPDFFile();
    removePage(1);
}

void PDFEdit::readPDFFile()
{
    pdf->load(pdfFileName);
    pageCount = pdf->pageCount();
}

void PDFEdit::removePage(int page)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/Users/Dawn/Desktop/output.pdf");

    QPainter painter(&printer);
    //for (int i = 0; i < pageCount; ++i) {
    //    if (i != page) {
    //        QImage iamge = pdf->render(i, QPageSize::definitionSize(QPageSize::A4));
    //    }
    //}

    painter.end();
    pdf->close();
}