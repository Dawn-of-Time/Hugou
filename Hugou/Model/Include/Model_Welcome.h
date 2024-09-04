#pragma once

#include <QObject>

class WelcomeController;

class WelcomeModel : public QObject
{

    Q_OBJECT

public:
    WelcomeModel();

private:
    friend class WelcomeController;
};