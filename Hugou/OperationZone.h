#pragma once
#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QStyleOption>
#include <QPainter>
#include "ui_OperationZone.h"

class OperationZone :
    public QWidget
{
    Q_OBJECT

public:
    OperationZone(QWidget* parent);

    void dragEnterEvent(QDragEnterEvent* event) override
    {
        if (!event->mimeData()->urls()[0].fileName().right(3).compare("pdf"))
            event->acceptProposedAction();
        else
            event->ignore();
    }
    void dropEvent(QDropEvent* event) override
    {
        const QList<QUrl> urls = event->mimeData()->urls();
        //if (urls.size() > 1);
        QString filePath = urls.at(0).toLocalFile();
        if (!filePath.isEmpty())
        {
            emit signalAdd(filePath);
        }
    }
    void mousePressEvent(QMouseEvent* event) override
    {
        emit clicked();
    }
    void paintEvent(QPaintEvent*)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

signals:
    void clicked();
    void signalAdd(QString filePath);

protected slots:
    void searchFromExplorer();

private:
    Ui_OperationZone ui;
};