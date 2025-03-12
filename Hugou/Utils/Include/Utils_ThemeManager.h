#pragma once
#include "Controller/Include/Controller_GlobalTop.h"
#include "Utils_ConfigurationHelper.h"
#include "Utils_MessegeHelper.h"
#include <QObject>
#include <QThread>

QT_BEGIN_NAMESPACE

struct ThemeResource
{
    QString generalStyleSheet = "";
    QString asideBarStyleSheet = "";
    QString preferenceStyleSheet = "";
};

class ThemeManager :
    public QObject
{
    Q_OBJECT

public:
    ThemeManager(QList<QWidget*> objectList, QObject* parent);
    ~ThemeManager();
    void loadThemeResource(QString theme = "");
    void applyThemeResource(ThemeResource* themeResource);
    
signals:
    void SignalThemeResourcePrepared(ThemeResource* themeResource);
    void SignalApplyThemeResourceFinished();

private:
    friend class LoadThemeResourceThread;
    QString m_tempTheme = "";
    QString m_theme = "";
    QWidget* m_hugou;
    QWidget* m_asideBarView;
    QWidget* m_preferenceView;
    ThemeResource* m_themeResource;
    GlobalTopController::UsageGuard* m_globalTopUsagePermission;
    void applyThemeForStartup(ThemeResource* themeResource);
    void applyTheme(ThemeResource* themeResource);
};

class LoadThemeResourceThread :
    public QThread
{
    Q_OBJECT

public:
    LoadThemeResourceThread(const QString& theme) : m_theme(theme) { };
    void run() override;

signals:
    void SignalThemeResourcePreparedInThread(ThemeResource* themeResource, bool consistentFlag);

private:
    QString m_theme;
    ThemeResource* m_themeResource = new ThemeResource{};
    bool m_isConsistent = true;
    static ThemeResource* getDefaultThemeResource();
};


QT_END_NAMESPACE