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

signals:
    void clicked();
    void signalAdd(QString filePath);

protected slots:
    void searchFromExplorer();

private:
    Ui_OperationZone ui;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event);
};