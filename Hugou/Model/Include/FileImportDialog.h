#pragma once
#include <qdialog.h>
#include <QtWidgets>
#include <QObject>
#include "Const_Geometry.h"
#include "ButtonHoverWatcher.h"

QT_BEGIN_NAMESPACE

class FileImportDialog :
    public QDialog
{
    Q_OBJECT

public:
    QPoint mousePos;
    QWidget* background;
    QWidget* centralWidget;
    QHBoxLayout* centralLayout;
    QPushButton* uploadButton;
    QLabel* dragZone;
    QPushButton* helpButton;
    QPushButton* minimizeButton;
    QPushButton* closeButton;
    ButtonHoverWatcher* closeButtonHoverWatcher;

    FileImportDialog(QMainWindow* HugouClass);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void uploadSuccessed(QString fileName);

private slots:
    void upload();
};

QT_END_NAMESPACE