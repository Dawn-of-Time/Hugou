#pragma once
#include "View_GlobalTop.h"
#include "Assistance_PreferenceHelper.h"
#include "Const_DefaultTheme.h"
#include "Const_SuccessNote.h"
#include <QObject>
#include <QThread>

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
    ThemeManager(QWidget* hugou, QWidget* asideBarView, QWidget* preferenceView, GlobalTopView* globalTopView);
    ~ThemeManager();
    QString getTheme();
    void loadThemeResource(QString theme = "");
    void startToApplyThemeResource(const QString& theme);
    void applyThemeResource(ThemeResource* themeResource);
    void endToApplyThemeResourceFinished();
    
signals:
    void SignalThemeResourcePrepared(ThemeResource* themeResource, bool consistentFlag);
    void SignalUpdateThemeComboboxValue(QString value);

private:
    QList<QPair<QString, QString>> m_errorList;
    QString m_tempTheme = "";
    QString m_theme = "";
    QWidget* m_hugou;
    QWidget* m_asideBarView;
    QWidget* m_preferenceView;
    GlobalTopView* m_globalTopView;

    void applyThemeForStartup(ThemeResource* themeResource, bool consistentFlag);
    void applyTheme(ThemeResource* themeResource, bool consistentFlag);
};

class LoadThemeResourceThread :
    public QThread
{
    Q_OBJECT

public:
    LoadThemeResourceThread() { };
    void run() override;
    inline void setTheme(const QString& theme) { m_theme = theme; }
    inline ThemeResource* getThemeResource() { return m_themeResource; };
    inline bool getConsistentFlag() { return m_isConsistent; }

signals:
    void SignalThemeResourcePreparedInThread(ThemeResource* themeResource, bool consistentFlag);

private:
    QString m_theme;
    ThemeResource* m_themeResource = new ThemeResource{};
    bool m_isConsistent = true;

    ThemeResource* getDefaultThemeResource();
};
