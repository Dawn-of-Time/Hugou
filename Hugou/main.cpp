#include "View_Welcome.h"
#include "Model_Welcome.h"
#include "Controller_Welcome.h"
#include "View_Hugou.h"
#include "Model_Hugou.h"
#include "Controller_Hugou.h"
#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include <QQmlEngine>
#include <QDir>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    // 注册qml
    qmlRegisterType<HugouView>("HugouModules", 1, 0, "Hugou");
    // 字体载入
    QString fontDir = "Resource/font";
    QDir dir(fontDir);
    QStringList files = dir.entryList(QDir::Files);
    foreach(const QString & fileName, files) {
        QString filePath = dir.absoluteFilePath(fileName);
        QFontDatabase::addApplicationFont(filePath);
    }
    // 读取配置
    SettingsHelper* helper = SettingsHelper::getHelper();
    // 检查是否是首次登录
    //if (helper->settingsMap["firstBoot"] == "true")
    //{
    //    WelcomeView welcomeView;
    //    WelcomeModel welcomeModel;
    //    WelcomeController welcomeController(&welcomeView, &welcomeModel);
    //    helper->settingsMap["firstBoot"] = "false";
    //    welcomeView.exec();
    //}
    
    // 主构建
    HugouView hugouView;
    HugouModel hugouModel;
    HugouController hugouController(&hugouView, &hugouModel);
    hugouView.show();
    return a.exec();
}
