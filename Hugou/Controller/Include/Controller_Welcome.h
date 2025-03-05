#pragma once

#include "View/Include/View_Welcome.h"
#include "Model/Include/Model_Welcome.h"
#include "Assistance/Include/Assistance_PreferenceHelper.h"

class WelcomeController : public QObject
{

    Q_OBJECT

public:
    WelcomeController(WelcomeView* welcomeView, WelcomeModel* welcomeModel);

private:
    WelcomeView* m_welcomeView;
    WelcomeModel* m_welcomeModel;
};