#include "View_Welcome.h"
#include "Model_Welcome.h"
#include "Controller_Welcome.h"
#include "View_Hugou.h"
#include "Model_Hugou.h"
#include "Controller_Hugou.h"
#include "Var.h"
#include "Database.h"
#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include <QQmlEngine>
#include <QDir>
#include "vld.h"


int main(int argc, char* argv[])
{
    // 分辨率适配（含图片缩放质量调整）
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    
    // 初始化全局变量
    Var::getVar();

    QApplication a(argc, argv);
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
    // 创建数据库
    Database db;
    // 读取配置
    PreferenceHelper* helper = PreferenceHelper::getHelper();
    // 检查是否是首次登录
    //if (helper->preferenceMap["firstBoot"] == "true")
    //{
    //    WelcomeView welcomeView;
    //    WelcomeModel welcomeModel;
    //    WelcomeController welcomeController(&welcomeView, &welcomeModel);
    //    helper->preferenceMap["firstBoot"] = "false";
    //    welcomeView.exec();
    //}
    
    // 主构建
    HugouModel hugouModel;
    HugouView hugouView;
    HugouController hugouController(&hugouView, &hugouModel);
    hugouView.show();
    return a.exec();
}
