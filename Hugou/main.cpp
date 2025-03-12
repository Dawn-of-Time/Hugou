#include "Controller/Include/Controller_Hugou.h"
#include "Controller/Include/Controller_Welcome.h"
#include "Database/Include/Database.h"
#include "Include/Global_Hugou.h"
#include "Model/Include/Model_Hugou.h"
#include "Model/Include/Model_Welcome.h"
#include "View/Include/View_Hugou.h"
#include "View/Include/View_Welcome.h"
#include "vld.h"
#include <QToolTip>
#include <QApplication>

int main(int argc, char* argv[])
{
    // 分辨率适配（含图片缩放质量调整）
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    qputenv("QT_SCALE_FACTOR", QString::number(0.9).toLatin1());

    QApplication a(argc, argv);
    
    // 创建数据库
    Database db;
    // 读取配置
    ConfigurationHelper* helper = ConfigurationHelper::getHelper();

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
    globalHugou = &hugouView;
    hugouView.show();
    return a.exec();
}
