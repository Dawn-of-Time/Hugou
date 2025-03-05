#pragma once
#include "View/Include/View_GlobalTop.h"
#include "Assistance_PreferenceHelper.h"
#include "Assistance_MessegeHelper.h"
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

// Ä¬ÈÏÖ÷Ìâ
const QString defaultGeneralStyleSheet =
QString("HugouView#hugou { background-color: #F0F4FD; }")
+ QString("QWidget#asideBarAndStackedWidget { background-color: transparent; }")
+ QString("QStackedWidget#stackedWidget { margin-bottom: 10px; margin-right: 10px; border-radius: 10px; background-color: rgba(255, 255, 255, 0.8);}");

const QString defaultAsideBarStyleSheet =
QString("QLabel { padding-left: 6px; color:#666666; background-color: transparent; }")
+ QString("QLabel#userAvatar { padding: 0px; border-radius: 24px; border: none; color: balck; background-color: transparent;} ")
+ QString("QLabel#userNickname { border: none; color: balck; background-color: transparent;} ")
+ QString("QLabel#userID { border: none; color: balck; background-color: transparent;} ")
+ QString("QPushButton[status=\"default\"] { border-radius: 10px; }")
+ QString("QPushButton[status=\"default\"] > QLabel { padding: 0px; margin :0px; color: #434343; background-color: transparent; }")
+ QString("QPushButton[status=\"current\"] { border-radius: 10px;}")
+ QString("QPushButton[status=\"current\"] > QLabel { padding: 0px; margin :0px; color: #377FED; background-color: transparent; }");

const QString defaultpreferenceStyleSheet =
QString("QStackedWidget { background-color: transparent; border: none }")
+ QString("QTreeWidget { background-color: transparent; border: none }")
+ QString("QListWidget { background-color: transparent; border: none; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px }")
+ QString("QListWidget::item:hover { background-color: transparent }")
+ QString("QPushButton { border: none }")
+ QString("QComboBox { border: none; border-radius: 5px; padding: 3px; background-color: #A2CBEE; }")
+ QString("QComboBox:hover { background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView { outline: none; margin-top: 5px; border-radius: 5px; background-color: #A2CBEE; }")
+ QString("QComboBox QAbstractItemView::item:hover { padding: 3px; color: black; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView::item:selected { padding: 3px; color: white; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox::down-arrow { image: url(\":/icon/down_bla.ico\"); width: 20px; }")
+ QString("QComboBox::drop-down { border: none; }");

