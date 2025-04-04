#include "Widgets/Include/Card/Card_Weather.h"

WeatherCard::WeatherCard(QWidget* parent)
	:Card(parent)
{
	ConfigurationHelper* helper = ConfigurationHelper::getHelper();
	helper->getRecordValue("weathercard_observationTime", m_observationTime);
	helper->getRecordValue("weathercard_temperature", m_temperature);
	helper->getRecordValue("weathercard_sensibleTemperature", m_sensibleTemperature);
	helper->getRecordValue("weathercard_icon", m_icon);
	helper->getRecordValue("weathercard_weather", m_weather);
	helper->getRecordValue("weathercard_wind360", m_wind360);
	helper->getRecordValue("weathercard_windDirection", m_windDirection);
	helper->getRecordValue("weathercard_windScale", m_windScale);
	helper->getRecordValue("weathercard_windSpeed", m_windSpeed);
	helper->getRecordValue("weathercard_humidity", m_humidity);
	helper->getRecordValue("weathercard_precipitationLastHour", m_precipitationLastHour);
	helper->getRecordValue("weathercard_pressure", m_pressure);
	helper->getRecordValue("weathercard_visibility", m_visibility);
	helper->getRecordValue("weathercard_cloud", m_cloud);
	helper->getRecordValue("weathercard_dewPointTemperature", m_dewPointTemperature);
	setupUi();
	LocationHelper* locationHelper = LocationHelper::getHelper();
	m_region = locationHelper->getRegion();

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [timer, locationHelper, this](){ tryToGetID(timer, locationHelper); });
	timer->start(1000);

	m_updateTimer = new QTimer(this);
	connect(m_updateTimer, &QTimer::timeout, this, &WeatherCard::tryToFetchData);
	connect(m_refreshButton, &QPushButton::clicked, this, &WeatherCard::refresh);
}

void WeatherCard::tryToGetID(QTimer* timer, LocationHelper* locationHelper)
{
	switch (locationHelper->status())
	{
	case LocationHelper::Prepared:
	{
		m_ID = locationHelper->getID();
		m_region = locationHelper->getRegion();
		timer->stop();
		tryToFetchData();
		m_updateTimer->start(3600000);
		break;
	}
	case LocationHelper::Error:
	{
		timer->stop();
		break;
	}
	default:
		break;
	}
}

void WeatherCard::tryToFetchData()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QUrl url("https://devapi.qweather.com/v7/weather/now");
	QUrlQuery query;
	query.addQueryItem("location", m_ID);
	query.addQueryItem("key", "b95fbc043bd6463d94abd98cd07c8ef5");
	query.addQueryItem("lang", "en");
	url.setQuery(query);
	QNetworkRequest request(url);
	QNetworkReply* reply = manager->get(request);
	connect(reply, &QNetworkReply::finished, [this, reply, manager]()
		{
			QString data = NetworkHelper::getHelper()->dealNetWorkReply(reply);
			if (!data.isEmpty())
			{
				QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
				QJsonObject jsonObject = jsonDocument.object();
				QString code = jsonObject.value("code").toString();
				if (code == "200")
				{
					QJsonObject liveObject = jsonObject.value("now").toObject();
					m_observationTime = liveObject.value("obsTime").toString();
					m_temperature = liveObject.value("temp").toString();
					m_sensibleTemperature = liveObject.value("feelsLike").toString();
					m_icon = liveObject.value("icon").toString();
					m_weather = liveObject.value("text").toString();
					m_wind360 = liveObject.value("wind360").toString();
					m_windDirection = liveObject.value("windDir").toString();
					m_windScale = liveObject.value("windScale").toString();
					m_windSpeed = liveObject.value("windSpeed").toString();
					m_humidity = liveObject.value("humidity").toString();
					m_precipitationLastHour = liveObject.value("precip").toString();
					m_pressure = liveObject.value("pressure").toString();
					m_visibility = liveObject.value("vis").toString();
					m_cloud = liveObject.value("cloud").toString();
					m_dewPointTemperature = liveObject.value("dew").toString();
					ConfigurationHelper* helper = ConfigurationHelper::getHelper();
					helper->setRecordValue("weathercard_observationTime", m_observationTime);
					helper->setRecordValue("weathercard_temperature", m_temperature);
					helper->setRecordValue("weathercard_sensibleTemperature", m_sensibleTemperature);
					helper->setRecordValue("weathercard_icon", m_icon);
					helper->setRecordValue("weathercard_weather", m_weather);
					helper->setRecordValue("weathercard_wind360", m_wind360);
					helper->setRecordValue("weathercard_windDirection", m_windDirection);
					helper->setRecordValue("weathercard_windScale", m_windScale);
					helper->setRecordValue("weathercard_windSpeed", m_windSpeed);
					helper->setRecordValue("weathercard_humidity", m_humidity);
					helper->setRecordValue("weathercard_precipitationLastHour", m_precipitationLastHour);
					helper->setRecordValue("weathercard_pressure", m_pressure);
					helper->setRecordValue("weathercard_visibility", m_visibility);
					helper->setRecordValue("weathercard_cloud", m_cloud);
					helper->setRecordValue("weathercard_dewPointTemperature", m_dewPointTemperature);
					updateUi();
				}
				reply->deleteLater();
				manager->deleteLater();
			}
			if (m_refreshButtonAnimation->state() == QPropertyAnimation::Running)
			{
				m_refreshButtonAnimation->stop();
				m_refreshButton->blockSignals(false);
				m_refreshButtonEffect->setEnabled(false);
			}
		});
}

void WeatherCard::refresh()
{
	m_updateTimer->stop();
	m_refreshButtonEffect->setEnabled(true);
	m_refreshButtonAnimation->start();
	m_refreshButton->blockSignals(true);
	LocationHelper* locationHelper = LocationHelper::getHelper();
	locationHelper->refresh();
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [timer, locationHelper, this]() { tryToGetID(timer, locationHelper); });
	timer->start(1000);
}

void WeatherCard::setupUi()
{
	// �����嵥
	const QFont addressFont = QFont("NeverMind", 14, QFont::Normal);
	const QFont recentUpdateFont = QFont("NeverMind", 10, QFont::Normal);
	const QFont temperatureFont = QFont("NeverMind", 24, QFont::DemiBold);
	const QFont weatherNameFont = QFont("NeverMind", 16, QFont::Light);
	const QFont informationTitleFont = QFont("NeverMind", 10, QFont::Normal);
	const QFont informationValueFont = QFont("NeverMind", 14, QFont::DemiBold);

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(10, 10, 10, 10);
	m_layout->setSpacing(15);

	m_titleWidget = new QWidget(this);
	m_titleWidget->setFixedHeight(30);
	m_titleWidgetLayout = new QHBoxLayout(m_titleWidget);
	m_titleWidgetLayout->setContentsMargins(5, 0, 5, 0);
	m_titleWidgetLayout->setSpacing(5);
	m_address = new QLabel(m_region, m_titleWidget);
	m_address->setFixedHeight(30);
	m_address->setFont(addressFont);
	m_recentUpdate = new QLabel("Recent Update:" + (m_observationTime.isEmpty() ? "N/A" : m_observationTime.mid(11, 5)), m_titleWidget);
	m_recentUpdate->setFixedHeight(30);
	m_recentUpdate->setFont(recentUpdateFont);
	m_refreshButton = new QPushButton(m_titleWidget);
	m_refreshButton->setFixedSize(20, 30);
	m_refreshButton->setIcon(QIcon(":/icon/refresh.ico"));
	m_refreshButton->setIconSize(QSize(18, 18));
	m_refreshButton->setCursor(Qt::PointingHandCursor);
	m_refreshButtonEffect = new QGraphicsOpacityEffect(m_refreshButton);
	m_refreshButtonEffect->setOpacity(1);
	m_refreshButton->setGraphicsEffect(m_refreshButtonEffect);
	m_refreshButtonEffect->setEnabled(false);
	m_refreshButtonAnimation = new QPropertyAnimation(m_refreshButtonEffect, "opacity", m_refreshButton);
	m_refreshButtonAnimation->setStartValue(1);
	m_refreshButtonAnimation->setKeyValueAt(0.5, 0);
	m_refreshButtonAnimation->setEndValue(1);
	m_refreshButtonAnimation->setDuration(1500);
	m_refreshButtonAnimation->setLoopCount(-1);
	m_titleWidgetLayout->addWidget(m_address);
	m_titleWidgetLayout->addStretch();
	m_titleWidgetLayout->addWidget(m_recentUpdate);
	m_titleWidgetLayout->addWidget(m_refreshButton);

	m_weatherWidget = new QWidget(this);
	m_weatherWidget->setFixedHeight(40);
	m_weatherWidgetLayout = new QHBoxLayout(m_weatherWidget);
	m_weatherWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_weatherWidgetLayout->setSpacing(20);
	m_weatherWidgetLayout->setAlignment(Qt::AlignHCenter);
	m_temperatureWidget = new QLabel((m_temperature.isEmpty() ? "N/A" : m_temperature) + "\u00B0C", m_weatherWidget);
	m_temperatureWidget->setFixedSize(90, 40);
	m_temperatureWidget->setFont(temperatureFont);
	m_temperatureWidget->setAlignment(Qt::AlignCenter);
	m_weatherNameWidget = new QLabel(m_weather.isEmpty() ? "N/A" : m_weather, m_weatherWidget);
	m_weatherNameWidget->setFixedHeight(40);
	m_weatherNameWidget->setFont(weatherNameFont);
	m_weatherNameWidget->setAlignment(Qt::AlignCenter);
	m_weatherWidgetLayout->addWidget(m_temperatureWidget);
	m_weatherWidgetLayout->addWidget(m_weatherNameWidget);


	m_informationWidget = new QWidget(this);
	m_informationWidget->setFixedHeight(40);
	m_informationWidgetLayout = new QHBoxLayout(m_informationWidget);
	m_informationWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_informationWidgetLayout->setSpacing(20);

	m_humidityWidget = new QWidget(m_informationWidget);
	m_humidityWidget->setFixedSize(80, 40);
	m_humidityWidgetLayout = new QVBoxLayout(m_humidityWidget);
	m_humidityWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_humidityWidgetLayout->setSpacing(2);
	m_humidityTitleWidget = new QLabel("Humidity", m_humidityWidget);
	m_humidityTitleWidget->setFixedSize(80, 14);
	m_humidityTitleWidget->setFont(informationTitleFont);
	m_humidityTitleWidget->setAlignment(Qt::AlignHCenter);
	m_humidityValueWidget = new QLabel((m_humidity.isEmpty() ? "N/A" : m_humidity) + "%", m_humidityWidget);
	m_humidityValueWidget->setFixedSize(80, 24);
	m_humidityValueWidget->setFont(informationValueFont);
	m_humidityValueWidget->setAlignment(Qt::AlignHCenter);
	m_humidityWidgetLayout->addWidget(m_humidityTitleWidget);
	m_humidityWidgetLayout->addWidget(m_humidityValueWidget);

	m_visibilityWidget = new QWidget(m_informationWidget);
	m_visibilityWidget->setFixedSize(80, 40);
	m_visibilityWidgetLayout = new QVBoxLayout(m_visibilityWidget);
	m_visibilityWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_visibilityWidgetLayout->setSpacing(2);
	m_visibilityTitleWidget = new QLabel("Visibility", m_visibilityWidget);
	m_visibilityTitleWidget->setFixedSize(80, 14);
	m_visibilityTitleWidget->setFont(informationTitleFont);
	m_visibilityTitleWidget->setAlignment(Qt::AlignHCenter);
	m_visibilityValueWidget = new QLabel((m_visibility.isEmpty() ? "N/A" : m_visibility) + "km", m_visibilityWidget);
	m_visibilityValueWidget->setFixedSize(80, 24);
	m_visibilityValueWidget->setFont(informationValueFont);
	m_visibilityValueWidget->setAlignment(Qt::AlignHCenter);
	m_visibilityWidgetLayout->addWidget(m_visibilityTitleWidget);
	m_visibilityWidgetLayout->addWidget(m_visibilityValueWidget);

	m_windWidget = new QWidget(m_informationWidget);
	m_windWidget->setFixedSize(80, 40);
	m_windWidgetLayout = new QVBoxLayout(m_windWidget);
	m_windWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_windWidgetLayout->setSpacing(2);
	m_windTitleWidget = new QLabel("Wind", m_windWidget);
	m_windTitleWidget->setFixedSize(80, 14);
	m_windTitleWidget->setFont(informationTitleFont);
	m_windTitleWidget->setAlignment(Qt::AlignHCenter);
	m_windValueWidget = new QLabel("Lv " + (m_windScale.isEmpty() ? "N/A" : m_windScale), m_windWidget);
	m_windValueWidget->setFixedSize(80, 24);
	m_windValueWidget->setFont(informationValueFont);
	m_windValueWidget->setAlignment(Qt::AlignHCenter);
	m_windWidgetLayout->addWidget(m_windTitleWidget);
	m_windWidgetLayout->addWidget(m_windValueWidget);

	m_informationWidgetLayout->addWidget(m_humidityWidget);
	m_informationWidgetLayout->addWidget(m_visibilityWidget);
	m_informationWidgetLayout->addWidget(m_windWidget);

	m_layout->addWidget(m_titleWidget);
	m_layout->addWidget(m_weatherWidget);
	m_layout->addWidget(m_informationWidget);
}

void WeatherCard::updateUi()
{
	m_address->setText(m_region);
	m_recentUpdate->setText("Recent Update:" + m_observationTime.mid(11, 5));
	m_recentUpdate->adjustSize();
	m_temperatureWidget->setText(m_temperature + "\u00B0C");
	m_weatherNameWidget->setText(m_weather);
	m_weatherNameWidget->adjustSize();
	m_weatherWidgetLayout->addWidget(m_temperatureWidget);
	m_weatherWidgetLayout->addWidget(m_weatherNameWidget);
	m_humidityValueWidget->setText(m_humidity + "%");
	m_visibilityValueWidget->setText(m_visibility + "km");
	m_windValueWidget->setText("Lv " + m_windScale);
}