#pragma once
#include <QObject>
#include <QEvent>
#include "FadeEffectButton.h"

class FadeEffectButtonHoverWatcher :
    public QObject
{
    Q_OBJECT

public:
    FadeEffectButtonHoverWatcher(QString default_res, QString hover_res, QSize iconSize, QObject* parent = nullptr);

private:
    QString default_res = "";
    QString hover_res = "";
    QSize iconSize;
    bool eventFilter(QObject* watched, QEvent* event) override;
};

