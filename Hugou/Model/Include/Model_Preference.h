#pragma once
#include <QObject>

class PreferenceController;

class PreferenceModel : public QObject
{

    Q_OBJECT

public:
    PreferenceModel(QObject* parent);

private:
    friend class PreferenceController;
};