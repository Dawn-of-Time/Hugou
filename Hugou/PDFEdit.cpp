#include "PDFEdit.h"

PDFEdit::PDFEdit(QString fileName) :
	QWidget()
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 主窗体
    centralFrame = new QFrame(this);
    centralFrame->setObjectName("centralFrame");
    centralFrame->setGeometry(QRect(0, 0, this->width(), this->height()));

    // 标题栏重构
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); //去除标题栏；支持单击任务栏图标最小化
    dragZone = new QLabel(this); // 拖拽区域
    dragZone->setObjectName("dragZone");
    dragZone->setGeometry(0, 0, this->width() - 5 * titleButtonWidth, titleButtonHeight);
    helpButton = new QPushButton(this); // 帮助按钮
    helpButton->setObjectName("helpButton");
    helpButton->setIcon(QIcon("res/help_b.png"));
    helpButton->setIconSize(QSize(18, 18));
    helpButton->setGeometry(this->width() - 4 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    minimizeButton = new QPushButton(this); // 最小化按钮
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setIcon(QIcon("res/minimize_b.png"));
    minimizeButton->setIconSize(QSize(18, 18));
    minimizeButton->setGeometry(this->width() - 3 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    islandButton = new QPushButton(this); // 岛屿按钮
    islandButton->setObjectName("islandButton");
    islandButton->setIcon(QIcon("res/island_b.png"));
    islandButton->setIconSize(QSize(18, 18));
    islandButton->setGeometry(this->width() - 2 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    islandButtonHoverWatcher = new ButtonHoverWatcher(QString("res/island_b.png"), QString("res/island_w.png"), this);
    islandButton->installEventFilter(islandButtonHoverWatcher);
    closeButton = new QPushButton(this);  // 关闭按钮
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