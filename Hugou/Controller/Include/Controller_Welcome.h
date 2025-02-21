#pragma once

#include "Var.h"
#include "View_Welcome.h"
#include "Model_Welcome.h"
#include "Assistance_PreferenceHelper.h"

class WelcomeController : public QObject
{

    Q_OBJECT

public:
    WelcomeController(WelcomeView* welcomeView, WelcomeModel* welcomeModel);

private:
    WelcomeView* m_welcomeView;
    WelcomeModel* m_welcomeModel;
};