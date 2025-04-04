#pragma once
#include "Controller/Include/Controller_GlobalTop.h"
#include "Utils_ConfigurationHelper.h"
#include "Utils_MessegeHelper.h"
#include <QObject>
#include <QThread>
#include <QApplication>

QT_BEGIN_NAMESPACE

enum ThemeRole
{
    General,
    AsideBar,
    Preference,
    Schedule
};

class ThemeManager :
    public QObject
{
    Q_OBJECT

public:
    static ThemeManager* getManager();
    void loadThemeResource(QString theme = "");
    QString& getStyleSheet(const ThemeRole& themeRole);
    
signals:
    void SignalThemeResourcePrepared();
    void SignalApplyThemeResourceFinished();
    void SignalApplyThemeResource(const QMap<ThemeRole, QString>& themeResourceMap);

private:
    friend class LoadThemeResourceThread;
    QString m_tempTheme = "";
    QString m_theme = "";
    QMap<ThemeRole, QString> m_themeResourceMap;
    QMap<ThemeRole, QString> m_cacheMap;
    GlobalTopController::UsageGuard* m_globalTopUsagePermission;
    ThemeManager();
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;
    void applyThemeForStartup();
    void applyTheme();
};

class LoadThemeResourceThread :
    public QThread
{
    Q_OBJECT

public:
    LoadThemeResourceThread(const QString& theme) : m_theme(theme){ };
    void run() override;

signals:
    void SignalThemeResourcePreparedInThread(QMap<ThemeRole, QString> themeResourceMap, bool consistentFlag, QMap<ThemeRole, QString> cacheMap = {});

private:
    enum ThemeResourceLoadMode
    {
        DeleteAfterLoading,     // 首次加载后，将样式表删除
        CacheAfterLoading,      // 首次加载后，将样式表缓存
    };
    QString m_theme;
    QString m_themeResource;
    QStringList m_fileNameList = { "general", "asideBar", "schedule"};
    QMap<QString, ThemeRole> m_themeRoleMap =
    {
        {"general", ThemeRole::General},
        {"asideBar", ThemeRole::AsideBar},
        {"preference", ThemeRole::Preference},
        {"schedule", ThemeRole::Schedule},
    };
    QMap<ThemeRole, ThemeResourceLoadMode> m_themeResourceLoadModeMap =
    {
        {ThemeRole::General, ThemeResourceLoadMode::DeleteAfterLoading},
        {ThemeRole::AsideBar, ThemeResourceLoadMode::CacheAfterLoading},
        {ThemeRole::Preference, ThemeResourceLoadMode::DeleteAfterLoading},
        {ThemeRole::Schedule, ThemeResourceLoadMode::DeleteAfterLoading}
    };
    QMap<ThemeRole, QString> m_themeResourceMap;
    QMap<ThemeRole, QString> m_cacheMap;
    bool m_isConsistent = true;
    static QString getDefaultThemeResource(const ThemeRole& themeRole);
};


QT_END_NAMESPACE