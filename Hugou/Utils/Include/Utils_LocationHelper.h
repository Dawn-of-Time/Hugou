#pragma once
#include <QObject>
#include "Utils_NetworkHelper.h"
#include "Utils_ConfigurationHelper.h"

class LocationHelper :
    public QObject
{
    Q_OBJECT

public:
    enum LocationResuorceStatus
    {
        NotPrepared,
        Prepared,
        Error
    };
    static LocationHelper* getHelper();
    LocationResuorceStatus status() { return m_status; };
    QString getID() { return m_ID; };
    QString getRegion() { return m_region; }

private:
    LocationResuorceStatus m_status = LocationResuorceStatus::NotPrepared;
    QString m_ID = "";
    QString m_province = "";
    QString m_region = "";
    LocationHelper();
    LocationHelper(const LocationHelper&) = delete;
    LocationHelper& operator=(const LocationHelper&) = delete;

    void getID(QNetworkReply* IDReply, QNetworkAccessManager* manager);
    void getProvinceAndRegion(QNetworkReply* provinceAndRegionReply, QNetworkAccessManager* manager);
};

