#include "OperationZone.h"
#include "File.h"

OperationZone::OperationZone(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	this->setAcceptDrops(true);
    connect(this, &OperationZone::clicked, this, &OperationZone::searchFromExplorer);
}

// 槽函数
void OperationZone::searchFromExplorer()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Choose PDF File"), "F:", QStringLiteral("(*pdf);"));
    if (!fileName.isEmpty())
    {
        emit signalAdd(fileName);
    }
}

// 重写父类函数
void OperationZone::dragEnterEvent(QDragEnterEvent* event)
{
    if (!event->mimeData()->urls()[0].fileName().right(3).compare("pdf"))
        event->acceptProposedAction();
    else
        event->ignore();
}

void OperationZone::dropEvent(QDropEvent* event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    //if (urls.size() > 1);
    QString filePath = urls.at(0).toLocalFile();
    if (!filePath.isEmpty())
    {
        emit signalAdd(filePath);
    }
}

void OperationZone::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

void OperationZone::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}