#include "FileImportDialog.h"

FileImportDialog::FileImportDialog(QMainWindow* HugouClass) :
    QDialog() // 不作为主窗口的子控件（可以移动至主窗口外）
{
	this->setFixedSize(functionDialogWidth, functionDialogHeight);
    this->move((QApplication::primaryScreen()->geometry().width() - functionDialogWidth) / 2, (QApplication::primaryScreen()->geometry().height() - functionDialogHeight) / 2);;
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); //去除标题栏；支持单击任务栏图标最小化
    
    // 标题栏重构
    dragZone = new QLabel(this); // 拖拽区域
    dragZone->setObjectName("dragZone");
    dragZone->setGeometry(0, 0, functionDialogWidth - 3 * titleButtonWidth, titleButtonHeight);
    helpButton = new QPushButton(this); // 帮助按钮
    helpButton->setObjectName("helpButton");
    helpButton->setIcon(QIcon("res/help_b.png"));
    helpButton->setIconSize(QSize(18, 18));
    helpButton->setGeometry(functionDialogWidth - 3 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    minimizeButton = new QPushButton(this); // 最小化按钮
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setIcon(QIcon("res/minimize_b.png"));
    minimizeButton->setIconSize(QSize(18, 18));
    minimizeButton->setGeometry(functionDialogWidth - 2 * titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    closeButton = new QPushButton(this);  // 关闭按钮
    closeButton->setObjectName("closeButton");
    closeButton->setIcon(QIcon("res/close_bla.png"));
    closeButton->setIconSize(QSize(18, 18));
    closeButton->setGeometry(functionDialogWidth - titleButtonWidth, 0, titleButtonWidth, titleButtonHeight);
    closeButtonHoverWatcher = new ButtonHoverWatcher(QString("res/close_bla.png"), QString("res/close_w.png"), this);
    closeButton->installEventFilter(closeButtonHoverWatcher);

    //background = new QWidget(HugouClass);
    //background->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight);
    //background->setStyleSheet("QWidget {border-bottom-left-radius: 12px; border-bottom-right-radius: 12px;background-color:rgba(0, 0, 0, 100);}");
    //this->raise();
    //background->stackUnder(this);
    //background->show();

    // 主体
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setGeometry(QRect(0, 0, functionDialogWidth, functionDialogHeight));
    centralWidget->lower();
    centralLayout = new QHBoxLayout(centralWidget);
    uploadButton = new QPushButton("UPLOAD PDF", centralWidget);
    uploadButton->setFixedSize(200, 50);
    uploadButton->setFont(QFont("Hind Siliguri", 20));
    uploadButton->setStyleSheet("QPushButton {border-radius: 25px; color: white; background-color: green}");
    centralLayout->addWidget(uploadButton);

    connect(minimizeButton, &QPushButton::clicked, this, &QDialog::showMinimized);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    connect(uploadButton, &QPushButton::clicked, this, &FileImportDialog::upload);

    QString centralWidgetStyleSheet = QString(
        "QWidget {border-radius: 12px; background-color: white;}");
    QString helpButtonStyleSheet = QString(
        "QPushButton {border-radius: 0px; background-color: white;}"
        "QPushButton:hover {background-color: #cccccc}");
    QString minimizeButtonStyleSheet = QString(
        "QPushButton {border-radius: 0px; background-color: white;}"
        "QPushButton:hover {background-color: #cccccc}");
    QString closeButtonStyleSheet = QString(
        "QPushButton {border-top-right-radius: 12px; background-color: white;}"
        "QPushButton:hover {background-color: red}");
    QString dragZoneStyleSheet = QString(
        "QLabel {border-top-left-radius: 12px; background-color: white;}");
    this->centralWidget->setStyleSheet(centralWidgetStyleSheet);
    this->dragZone->setStyleSheet(dragZoneStyleSheet);
    this->minimizeButton->setStyleSheet(minimizeButtonStyleSheet);
    this->helpButton->setStyleSheet(helpButtonStyleSheet);
    this->closeButton->setStyleSheet(closeButtonStyleSheet);
}

void FileImportDialog::mousePressEvent(QMouseEvent* event)
{
    mousePos = event->globalPos() - pos();
}

void FileImportDialog::mouseMoveEvent(QMouseEvent* event)
{
    if (this->dragZone->underMouse()) {
        move(event->globalPos() - mousePos);
    }
}

// 槽函数
void FileImportDialog::upload()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Choose PDF File"), "F:", QStringLiteral("(*pdf);"));
    if (!fileName.isEmpty())
    {
        emit uploadSuccessed(fileName);
    }
}