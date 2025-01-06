#pragma once
#include <QObject>
#include <QEvent>
#include "IconTextButton.h"

class IconTextButtonHoverWatcher :
    public QObject
{
    Q_OBJECT

public:
    IconTextButtonHoverWatcher(QString default_res, QString hover_res, QSize iconSize, QObject* parent = nullptr);

private:
    QString default_res = "";
    QString hover_res = "";
    QSize iconSize;
    bool eventFilter(QObject* watched, QEvent* event) override;
};

