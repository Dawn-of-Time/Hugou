#pragma once
#include <QObject>

class PreferenceController;

class PreferenceModel : public QObject
{

    Q_OBJECT

public:
    PreferenceModel();

private:
    friend class PreferenceController;
};