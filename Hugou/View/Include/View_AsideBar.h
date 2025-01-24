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
    QWidget* m_userWidget;
    QHBoxLayout* m_userWidgetLayout;
    QLabel* m_userAvatar;
    QWidget* m_userNicknameAndIDWidget;
    QVBoxLayout* m_userNicknameAndIDWidgetLayout;
    QLabel* m_userNickname;
    QLabel* m_userID;
    QLabel* m_planLabel;
    IconTextButton* m_scheduleButton;
    QLabel* m_dataBaseLabel;
    IconTextButton* m_documentButton;
    IconTextButton* m_recordButton;
    IconTextButton* m_settingButton;
    ButtonHoverWatcher* m_scheduleButtonHoverWatcher;
    ButtonHoverWatcher* m_settingButtonHoverWatcher;
    QList<IconTextButton*> m_asideBarButtonList;
    const QList<QStringList> m_asideBarButtonIconList = 
    { 
        {":/icon/schedule_default_16.png", ":/icon/schedule_current_16.png"},
        {":/icon/document_default_16.png", ":/icon/document_current_16.png"}
    };

    void setupUi();
    void switchOverStackedWidget(int index);
    QPixmap cropPixmapIntoCircle(QPixmap& pixmap, int diameter)
    { 
        double factor = getScale();
        int width = pixmap.width();
        int height = pixmap.height();
        diameter = qMin(diameter, qMin(width, height));

        QBitmap bitmap(width, height);
        bitmap.fill(Qt::color0);
        QPainter painter(&bitmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::color1);
        painter.translate(0, 0);
        painter.drawEllipse(0, 0, width, height);
        QPixmap result = pixmap.copy();
        result.setDevicePixelRatio(factor);
        result.setMask(bitmap);
        return result;
    }
};