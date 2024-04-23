#include "Hugou.h"
#include "Setting.h"
#include <QtWidgets/QApplication>
#include <QQmlEngine>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);
    // 注册qml
    qmlRegisterType<Hugou>("HugouModules", 1, 0, "Hugou");
    // 字体载入
    QString fontDir = "res/font";
    QDir dir(fontDir);
    QStringList files = dir.entryList(QDir::Files);
    foreach(const QString & fileName, files) {
        QString filePath = dir.absoluteFilePath(fileName);
        QFontDatabase::addApplicationFont(filePath);
    }
    // 设置读取与应用
    Setting* setting = new Setting();
    // 主构建
    Hugou w(setting);
    w.show();
    return a.exec();
}
