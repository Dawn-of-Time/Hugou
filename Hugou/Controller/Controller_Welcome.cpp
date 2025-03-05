#include "Controller/Include/Controller_Welcome.h"

WelcomeController::WelcomeController(WelcomeView* welcomeView, WelcomeModel* welcomeModel)
    : QObject()
{
    m_welcomeView = welcomeView;
    m_welcomeModel = welcomeModel;
}