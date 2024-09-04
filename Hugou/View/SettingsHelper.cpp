#include "SettingsHelper.h"

QWidget* SettingsHelper::m_hugou = nullptr;
SettingsHelper* SettingsHelper::m_helper = nullptr;
QMutex SettingsHelper::m_mutex;

SettingsHelper::SettingsHelper()
    : QObject()
{
    verifyAndLoadSettings();
    connect(this, &SettingsHelper::triggerError, this, &SettingsHelper::dealError);
}

SettingsHelper* SettingsHelper::getHelper() {
    if (m_helper == nullptr) {
        QMutexLocker locker(&m_mutex);
        // 再次检查实例是否为空，防止多线程同时创建实例（双重检查锁定）  
        if (m_helper == nullptr) {
            m_helper = new SettingsHelper();
        }
    }
    return m_helper;
}

void SettingsHelper::verifyAndLoadSettings()
{
    if (!verifyConfINIExist()) return;
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    QStringList confINIList = confINI.allKeys();
    // 配置项完整性校验
    for (const QString& key : settingsKeyList)
    {
        if (!confINI.allKeys().contains(key))
        {
            emit triggerError(10001);
            return;
        }
    }

    // 配置项合法性校验
    bool verifyFlag = true;
    for(const QString& key : settingsKeyList) {
        QStringList values = settingsValueMap[key];
        QString value = confINI.value(key, "invalid").toString();
        if (!values.contains(value))
        {
            verifyFlag = false;
            settingsMap.insert(key, defalutSettingsValueMap[key]);
        }
        else settingsMap.insert(key, value);
    }
    if (!verifyFlag) emit triggerError(10002);
}

QString SettingsHelper::readSettings(QString key)
{
    if (!verifyConfINIExist()) return "notExist";
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    return confINI.value(key, "invalid").toString();
}

bool SettingsHelper::writeSettings(QString key, QString value)
{
    if (!verifyConfINIExist()) return false;
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    confINI.setValue(key, value);
    return true;
}

void SettingsHelper::syncSettings()
{
    if (!verifyConfINIExist()) return;
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    confINI.sync();
}

// 槽函数
void SettingsHelper::dealError(int errorCode)
{
    QSettings errorCodeINI("Configuration/errorCode.ini", QSettings::IniFormat);
    QSettings solutionINI("Configuration/solution.ini", QSettings::IniFormat);
    QString content = errorCodeINI.value(QString::number(errorCode), "Unknown error code.").toString() + "(Error Code: " + QString::number(errorCode) + ")";
    QString subcontent = solutionINI.value(QString::number(errorCode), "No solution found.").toString();
    if (m_hugou) floatingNoteManager.raiseFloatingNote(m_hugou, FloatingNote::Error, content, subcontent);
}

bool SettingsHelper::verifyConfINIExist()
{
    if (!QFile("Configuration/conf.ini").exists())
    {
        emit triggerError(10000);
        return false;
    }
    return true;
}

//bool SettingsHelper::verifyConfINIInvalid()
//{
//    if (!QFile("conf.ini").exists())
//    {
//        emit triggerError(1000);
//        return false;
//    }
//    QStringList value = settingValueMap.find(key)->second;
//    if (!value.contains((confINI.value(key, "invalid").toString())))
//    {
//        emit triggerError(1002);
//        return false;
//    }
//    return true;
//}