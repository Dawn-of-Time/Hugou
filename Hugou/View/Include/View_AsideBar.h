#pragma once
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QPainter>
#include <QBitmap>
#include "Const_Geometry.h"
#include "IconTextButton.h"
#include "ButtonHoverWatcher.h"
#include "Var.h"

class AsideBarView : public QWidget
{
    Q_OBJECT

public:
    AsideBarView(QWidget* parent);

signals:
    void SignalChangeStackedWidget(int index);

private:
    QVBoxLayout* m_asideBarLayout;
    QList<IconTextButton*> m_asideBarButtonList;

    // ×ÖÌåÇåµ¥
    const QFont asideTitleFont = QFont("NeverMind", 10, QFont::Normal);
    const QFont asideButtonFont = QFont("NeverMind", 12, QFont::Normal);

    enum class ItemType {
        AsideTitle,
        AsideButton,
        Stretch
    };
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
        {tr("Schedule"), qMakePair(ItemType::AsideButton, QStringList({":/icon/schedule_default_16.png", ":/icon/schedule_current_16.png"}))},
        {tr("Project"), qMakePair(ItemType::AsideButton, QStringList({":/icon/project_default_16.png", ":/icon/project_current_16.png"}))},
        {tr("Achievement"), qMakePair(ItemType::AsideButton, QStringList({":/icon/achievement_default_16.png", ":/icon/achievement_current_16.png"}))},

        {tr("Database"), qMakePair(ItemType::AsideTitle, QStringList())},
        {tr("Document"), qMakePair(ItemType::AsideButton, QStringList({":/icon/document_default_16.png", ":/icon/document_current_16.png"}))},
        {tr("Application Repo"), qMakePair(ItemType::AsideButton, QStringList({":/icon/application_repo_default_16.png", ":/icon/application_repo_current_16.png"}))},

        {tr("Addition"), qMakePair(ItemType::AsideTitle, QStringList())},
        {tr("Extension"), qMakePair(ItemType::AsideButton, QStringList({":/icon/extension_default_16.png", ":/icon/extension_current_16.png"}))},
        
        {"Stretch", qMakePair(ItemType::Stretch, QStringList())},

        {tr("Recycle Bin"), qMakePair(ItemType::AsideButton, QStringList({":/icon/recycle_bin_default_16.png", ":/icon/recycle_bin_current_16.png"}))},
        {tr("Preference"), qMakePair(ItemType::AsideButton, QStringList({":/icon/preference_default_16.png", ":/icon/preference_current_16.png"}))}
    };
    void setupUi();
    QLabel* generateTitle(QString titleText);
    IconTextButton* generateButton(QString buttonText);
    void switchOverStackedWidget();
};