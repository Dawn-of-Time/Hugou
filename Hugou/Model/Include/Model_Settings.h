#pragma once
#include <QObject>

class SettingsController;

class SettingsModel : public QObject
{

    Q_OBJECT

public:
    SettingsModel();

private:
    friend class SettingsController;
};