#include "SettingsHelper.h"

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
        floatingNoteManager.raiseFloatingNote(m_hugou, FloatingNote::Error, error.first, error.second);
    }
}

void SettingsHelper::verifyAndLoadSettings()
{
    if (!verifyConfINIExist()) return;
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    QStringList confINIList = confINI.allKeys();
    bool integralityFlag = true;
    bool validityFlag = true;
    for (const QString& key : settingsKeyList)
    {
        // 配置项完整性校验
        if (!confINI.allKeys().contains(key))
        {
            integralityFlag = false;
            m_settingsMap.insert(key, defalutSettingsValueMap[key]);
            continue;
        }
        // 配置项合法性校验
        QStringList values = settingsValueMap[key];
        QString value = confINI.value(key, "").toString();
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
    if (!integralityFlag) emit triggerError(10001);
    if (!validityFlag) emit triggerError(10002);
}

QString SettingsHelper::readSettings(QString key)
{
    if (!verifyConfINIExist()) return "notExist";
    QSettings confINI("Configuration/conf.ini", QSettings::IniFormat);
    return confINI.value(key, "invalid").toString();
}

// writeSettings函数包含了程序内配置映射表的写入和ini配置文件的写入。
bool SettingsHelper::writeSettings(QString key, QString value)
{
    if (!verifyConfINIExist()) return false;
    m_settingsMap[key] = value;
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
    else m_errorList.append(qMakePair(content, subcontent));
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