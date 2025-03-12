#include "Utils/Include/Utils_LocationHelper.h"

LocationHelper::LocationHelper()
	:QObject()
{
	ConfigurationHelper* helper = ConfigurationHelper::getHelper();
	helper->getRecordValue("location_ID", m_ID);
	helper->getRecordValue("location_region", m_region);
	m_region = m_region.isEmpty() ? "Unknown" : m_region;
	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QNetworkReply* provinceAndRegionReply = manager->get(QNetworkRequest(QUrl("https://whois.pconline.com.cn/ipJson.jsp?json=true")));
	connect(provinceAndRegionReply, &QNetworkReply::finished, [this, provinceAndRegionReply, manager]() {getProvinceAndRegion(provinceAndRegionReply, manager); });
}

void LocationHelper::getProvinceAndRegion(QNetworkReply* provinceAndRegionReply, QNetworkAccessManager* manager)
{
	QString data = NetworkHelper::getHelper()->dealNetWorkReply(provinceAndRegionReply);
	if (!data.isEmpty())
	{
		QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
		QJsonObject jsonObject = jsonDocument.object();
		m_province = jsonObject.value("pro").toString();
		m_region = jsonObject.value("region").toString();
		QUrl url("https://geoapi.qweather.com/v2/city/lookup");
		QUrlQuery query;
		query.addQueryItem("location", m_region);
		query.addQueryItem("adm", m_province);
		query.addQueryItem("key", "b95fbc043bd6463d94abd98cd07c8ef5");
		query.addQueryItem("lang", "en");
		url.setQuery(query);
		QNetworkReply* IDReply = manager->get(QNetworkRequest(url));
		connect(IDReply, &QNetworkReply::finished, [this, IDReply, manager]() {getID(IDReply, manager); });
		provinceAndRegionReply->deleteLater();
	}
	else m_status = LocationResuorceStatus::Error;
}

void LocationHelper::getID(QNetworkReply* IDReply, QNetworkAccessManager* manager)
{
	QString data = NetworkHelper::getHelper()->dealNetWorkReply(IDReply);
	if (!data.isEmpty())
	{
		QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
		QJsonObject jsonObject = jsonDocument.object();
		QJsonArray jsonArray = jsonObject.value("location").toArray();
		QJsonObject locationObject = jsonArray[0].toObject();
		m_region = locationObject.value("name").toString();
		m_ID = locationObject.value("id").toString();
		ConfigurationHelper* helper = ConfigurationHelper::getHelper();
		helper->setRecordValue("location_ID", m_ID);
		helper->setRecordValue("location_region", m_region);
		QNetworkReply* geoReply = manager->get(QNetworkRequest(QUrl("https://ipapi.co/json/")));
		m_status = LocationResuorceStatus::Prepared;
		IDReply->deleteLater();
		manager->deleteLater();
	}
	else m_status = LocationResuorceStatus::Error;
}

void LocationHelper::refresh()
{
	m_status = LocationResuorceStatus::NotPrepared;
	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QNetworkReply* provinceAndRegionReply = manager->get(QNetworkRequest(QUrl("https://whois.pconline.com.cn/ipJson.jsp?json=true")));
	connect(provinceAndRegionReply, &QNetworkReply::finished, [this, provinceAndRegionReply, manager]() {getProvinceAndRegion(provinceAndRegionReply, manager); });
}

LocationHelper* LocationHelper::getHelper()
{
	static LocationHelper helper;
	return &helper;
}