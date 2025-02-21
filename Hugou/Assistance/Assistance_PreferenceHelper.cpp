#include "Assistance_PreferenceHelper.h"

PreferenceHelper::PreferenceHelper()
    : QObject()
{
    connect(this, &PreferenceHelper::triggerError, this, &PreferenceHelper::dealError);
    verifyAndLoadpreference();
}


PreferenceHelper* PreferenceHelper::getHelper() 
{
	static PreferenceHelper helper;
    return &helper;
}

void PreferenceHelper::setHugou(QWidget* hugou) 
{ 
    m_hugou = hugou;
    for (QPair<QString, QString>& error : m_errorList)
        FloatingNoteManager::getManager()->raiseFloatingNote(FloatingNote::Error, error.first, error.second);
}

void PreferenceHelper::verifyAndLoadpreference()
{
    if (!verifyConfINIExist()) return;
    QStringList confINIList = m_confINI.allKeys();
    bool integralityFlag = true;
    bool validityFlag = true;
    for (const QString& key : preferenceKeyList)
    {
        // 配置项完整性校验
        if (!confINIList.contains(key))
        {
            integralityFlag = false;
            m_preferenceMap.insert(key, defalutPreferenceValueMap[key]);
            continue;
        }
        // 配置项合法性校验
        QStringList values = preferenceValueMap[key];
        QString value = m_confINI.value(key, "").toString();
        if (values.isEmpty()) // 无需校验合法性
        {
            m_preferenceMap.insert(key, value);
            continue;
        }
        if (!values.contains(value))
        {
            validityFlag = false;
            m_preferenceMap.insert(key, defalutPreferenceValueMap[key]);
        }
        else m_preferenceMap.insert(key, value);
    }
    if (!integralityFlag) emit triggerError("10001");
    if (!validityFlag) emit triggerError("10002");
}

// 从ini配置文件读取
QString PreferenceHelper::readpreference(QString key)
{
    if (!verifyConfINIExist()) return "notExist";
    return m_confINI.value(key, "invalid").toString();
}

// 从映射表读取
bool PreferenceHelper::getpreferenceValue(QString key, QString& value)
{
    if (m_preferenceMap.contains(key))
    {
        value = m_preferenceMap[key];
        return true;
    }
    else
        return false;
}

// 写入映射表
void PreferenceHelper::setpreferenceValue(QString key, QString value)
{
    m_preferenceMap[key] = value;
    if (writepreference(key, value)) m_isChanged = true;
}

bool PreferenceHelper::writepreference(QString key, QString value)
{
    if (!verifyConfINIExist()) return false;
    m_confINI.setValue(key, value);
    return true;
}

void PreferenceHelper::syncpreference()
{
    if (m_isChanged)
    {
        if (!verifyConfINIExist()) return;
        m_confINI.sync();
    }
}

// 槽函数
void PreferenceHelper::dealError(QString errorCode, QString otherInfo)
{
    QSettings errorCodeINI("Configuration/errorCode.ini", QSettings::IniFormat);
    QSettings solutionINI("Configuration/solution.ini", QSettings::IniFormat);
    QString content = errorCodeINI.value(errorCode, "Unknown error code.").toString() + "(Error Code: " + errorCode + ")";
    QString subcontent = solutionINI.value(errorCode, "No solution found.").toString() + otherInfo;
    if (m_hugou) FloatingNoteManager::getManager()->raiseFloatingNote(FloatingNote::Error, content, subcontent);
    else m_errorList.append(qMakePair(content, subcontent));
}

bool PreferenceHelper::verifyConfINIExist()
{
    if (!QFile("Configuration/conf.ini").exists())
    {
        emit triggerError("10000");
        return false;
    }
    return true;
}

//bool PreferenceHelper::verifyConfINIInvalid()
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