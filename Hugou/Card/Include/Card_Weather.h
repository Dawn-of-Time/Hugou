#pragma once
#include "Card.h"
#include "Utils/Include/Utils_LocationHelper.h"
#include "Utils/Include/Utils_ConfigurationHelper.h"
#include <QTimer>

class WeatherCard :
    public Card
{
public:
    WeatherCard(QWidget* parent);

private:
    QTimer* m_updateTimer;
    QString m_ID = "";
    QString m_region = "Unknown";
    QString m_observationTime = "";
    QString m_temperature = "";
    QString m_sensibleTemperature = "";
    QString m_icon = "";
    QString m_weather = "";
    QString m_wind360 = "";
    QString m_windDirection = "";
    QString m_windScale = "";
    QString m_windSpeed = "";
    QString m_humidity = "";
    QString m_precipitationLastHour = "";
    QString m_pressure = "";
    QString m_visibility = "";
    QString m_cloud = "";
    QString m_dewPointTemperature = "";

    QVBoxLayout* m_layout;
    QWidget* m_titleWidget;
    QHBoxLayout* m_titleWidgetLayout;
    QLabel* m_address;
    QLabel* m_recentUpdate;
    QPushButton* m_refreshButton;
    QWidget* m_weatherWidget;
    QHBoxLayout* m_weatherWidgetLayout;
    QLabel* m_temperatureWidget;
    QLabel* m_weatherNameWidget;
    QWidget* m_informationWidget;
    QHBoxLayout* m_informationWidgetLayout;
    QWidget* m_humidityWidget;
    QVBoxLayout* m_humidityWidgetLayout;
    QLabel* m_humidityTitleWidget;
    QLabel* m_humidityValueWidget;
    QWidget* m_visibilityWidget;
    QVBoxLayout* m_visibilityWidgetLayout;
    QLabel* m_visibilityTitleWidget;
    QLabel* m_visibilityValueWidget;
    QWidget* m_windWidget;
    QVBoxLayout* m_windWidgetLayout;
    QLabel* m_windTitleWidget;
    QLabel* m_windValueWidget;

    void tryToGetID(QTimer* timer, LocationHelper* locationHelper);
    void tryToFetchData();
    void setupUi();
    void updateUi();
};

