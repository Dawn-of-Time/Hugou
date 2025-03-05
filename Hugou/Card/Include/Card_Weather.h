#pragma once
#include "Card.h"
#include "Assistance/Include/Assistance_LocationHelper.h"
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
    QString m_observationTime = "N/A";
    QString m_temperature = "N/A";
    QString m_sensibleTemperature = "N/A";
    QString m_icon = "N/A";
    QString m_weather = "N/A";
    QString m_wind360 = "N/A";
    QString m_windDirection = "N/A";
    QString m_windScale = "N/A";
    QString m_windSpeed = "N/A";
    QString m_humidity = "N/A";
    QString m_precipitationLastHour = "N/A";
    QString m_pressure = "N/A";
    QString m_visibility = "N/A";
    QString m_cloud = "N/A";
    QString m_dewPointTemperature = "N/A";

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

