#include "Assistance_SettingsHelper.h"

QWidget* SettingsHelper::m_hugou = nullptr;
SettingsHelper* SettingsHelper::m_helper = nullptr;
QMutex SettingsHelper::m_mutex;

SettingsHelper::SettingsHelper()
    : QObject()
{
    connect(this, &SettingsHelper::triggerError, this, &SettingsHelper::dealError);
    verifyAndLoadSettings();
}

SettingsHelper* SettingsHelper::getHelper() 
{
    if (m_helper == nullptr) {
        QMutexLocker locker(&m_mutex);
        // 再次检查实例是否为空，防止多线程同时创建实例（双重检查锁定）  
        if (m_helper == nullptr) {
            m_helper = new SettingsHelper();
        }
    }
    return m_helper;
}

void SettingsHelper::setHugou(QWidget* hugou) 
{ 
    m_hugou = hugou;
    for (QPair<QString, QString>& error : m_errorList)
    {
        FloatingNoteManager::getManager()->raiseFloatingNote(FloatingNote::Error, error.first, error.second);
    }
}

void SettingsHelper::verifyAndLoadSettings()
{
    if (!verifyConfINIExist()) return;
    QStringList confINIList = m_confINI.allKeys();
    bool integralityFlag = true;
    bool validityFlag = true;
    for (const QString& key : settingsKeyList)
    {
        // 配置项完整性校验
        if (!m_confINI.allKeys().contains(key))
        {
            integralityFlag = false;
            m_settingsMap.insert(key, defalutSettingsValueMap[key]);
            continue;
        }
        // 配置项合法性校验
        QStringList values = settingsValueMap[key];
        QString value = m_confINI.value(key, "").toString();
        if (values.isEmpty()) // 无需校验合法性
        {
            m_settingsMap.insert(key, value);
            continue;
        }
        if (!values.contains(value))
        {
            validityFlag = false;
            m_settingsMap.insert(key, defalutSettingsValueMap[key]);
        }
        else m_settingsMap.insert(key, value);
    }
    if (!integralityFlag) emit triggerError("10001");
    if (!validityFlag) emit triggerError("10002");
}

// 从ini配置文件读取
QString SettingsHelper::readSettings(QString key)
{
    if (!verifyConfINIExist()) return "notExist";
    return m_confINI.value(key, "invalid").toString();
}

// 从映射表读取
bool SettingsHelper::getSettingsValue(QString key, QString& value)
{
    if (m_settingsMap.contains(key))
    {
        value = m_settingsMap[key];
        return true;
    }
    else
        return false;
}

// 写入映射表
void SettingsHelper::setSettingsValue(QString key, QString value)
{
    m_settingsMap[key] = value;
    if (writeSettings(key, value)) m_isChanged = true;
}

bool SettingsHelper::writeSettings(QString key, QString value)
{
    if (!verifyConfINIExist()) return false;
    m_confINI.setValue(key, value);
    return true;
}

void SettingsHelper::syncSettings()
{
    if (m_isChanged)
    {
        if (!verifyConfINIExist()) return;
        m_confINI.sync();
    }
}

// 槽函数
void SettingsHelper::dealError(QString errorCode, QString otherInfo)
{
    QSettings errorCodeINI("Configuration/errorCode.ini", QSettings::IniFormat);
    QSettings solutionINI("Configuration/solution.ini", QSettings::IniFormat);
    QString content = errorCodeINI.value(errorCode, "Unknown error code.").toString() + "(Error Code: " + errorCode + ")";
    QString subcontent = solutionINI.value(errorCode, "No solution found.").toString() + otherInfo;
    if (m_hugou) FloatingNoteManager::getManager()->raiseFloatingNote(FloatingNote::Error, content, subcontent);
    else m_errorList.append(qMakePair(content, subcontent));
}

bool SettingsHelper::verifyConfINIExist()
{
    if (!QFile("Configuration/conf.ini").exists())
    {
        emit triggerError("10000");
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