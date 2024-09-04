#pragma once
#include <Qthread>
#include <QFile>
#include <QString>
#include "SettingsHelper.h"

class ThemeLoadThread :
    public QThread
{
    Q_OBJECT

public:
    ThemeLoadThread(QString theme);
    void run() override;

signals:
    void themeResourcePrepared(QString generalStyleFile, QString asideBarStyleFile, QString settingsStyleFile);

private:
    QString m_theme;
};

