#pragma once
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QPainter>
#include <QBitmap>
#include <QFont>
#include "Include/Const_Geometry.h"
#include "View/Include/FadeEffectButton.h"

class AsideBarView : public QWidget
{
    Q_OBJECT

public:
    AsideBarView(QWidget* parent);

signals:
    void SignalChangeStackedWidget(int index);

private:
    QVBoxLayout* m_asideBarLayout;
    QList<FadeEffectButton*> m_asideBarButtonList;

    enum class ItemType {
        AsideTitle,
        AsideButton,
        Stretch
    };
    // ÒÔ¿Õ×Ö·û´®·Ö¸ôÕÂ(Chapter)
    const QStringList asideBarList =
    {
        tr("Plan"),
        tr("Schedule"),
        tr("Project"),
        tr("Achievement"),
        "",
        tr("Database"),
        tr("Document"),
        tr("Application Repo"),
        "",
        tr("Addition"),
        tr("Extension"),
        "Stretch",
        tr("Recycle Bin"),
        tr("Preference")
    };

    const QMap<QString, QPair<ItemType, QStringList>> m_asideBarItemIconMap =
    {
        {tr("Plan"), qMakePair(ItemType::AsideTitle, QStringList())},
        {tr("Schedule"), qMakePair(ItemType::AsideButton, QStringList({":/icon/schedule_default.ico", ":/icon/schedule_current.ico"}))},
        {tr("Project"), qMakePair(ItemType::AsideButton, QStringList({":/icon/project_default.ico", ":/icon/project_current.ico"}))},
        {tr("Achievement"), qMakePair(ItemType::AsideButton, QStringList({":/icon/achievement_default.ico", ":/icon/achievement_current.ico"}))},

        {tr("Database"), qMakePair(ItemType::AsideTitle, QStringList())},
        {tr("Document"), qMakePair(ItemType::AsideButton, QStringList({":/icon/document_default.ico", ":/icon/document_current.ico"}))},
        {tr("Application Repo"), qMakePair(ItemType::AsideButton, QStringList({":/icon/application_repo_default.ico", ":/icon/application_repo_current.ico"}))},

        {tr("Addition"), qMakePair(ItemType::AsideTitle, QStringList())},
        {tr("Extension"), qMakePair(ItemType::AsideButton, QStringList({":/icon/extension_default.ico", ":/icon/extension_current.ico"}))},
        
        {"Stretch", qMakePair(ItemType::Stretch, QStringList())},

        {tr("Recycle Bin"), qMakePair(ItemType::AsideButton, QStringList({":/icon/recycle_bin_default.ico", ":/icon/recycle_bin_current.ico"}))},
        {tr("Preference"), qMakePair(ItemType::AsideButton, QStringList({":/icon/preference_default.ico", ":/icon/preference_current.ico"}))}
    };
    void setupUi();
    QLabel* generateTitle(const QString& titleText);
    FadeEffectButton* generateButton(const QString& buttonText);
    void switchOverStackedWidget();
};