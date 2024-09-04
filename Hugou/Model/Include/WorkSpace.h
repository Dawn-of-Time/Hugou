#pragma once

#include <QWidget>
#include "ui_WorkSpace.h"

class WorkSpace :
    public QWidget
{
    Q_OBJECT

public:
    WorkSpace(QWidget* parent);

protected slots:
    void slotAdd(QString filePath);

private:
    Ui_WorkSpace ui;
};

