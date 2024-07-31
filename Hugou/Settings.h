#pragma once
#include <QWidget>
#include <QSettings>
#include <QPainter>
#include "ui_Settings.h"

class Settings :
    public QWidget
{
    Q_OBJECT

public:
    Settings(QWidget* parent);
    /*~Settings();*/


private:
    Ui_Settings ui;
};

