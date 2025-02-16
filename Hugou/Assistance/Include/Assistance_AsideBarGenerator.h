#pragma once
#include <QObject>
#include <QMap>
#include <QLabel>
#include "FadeEffectButton.h"

class AsideBarGenerator :
    public QObject
{
public:
    AsideBarGenerator(QWidget* asideBar);

private:
    QWidget* m_asideBar;
    
};

