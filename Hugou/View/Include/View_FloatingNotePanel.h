#pragma once
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include "View_FloatingNote.h"
#include "Const_Geometry.h"

class FloatingNotePanel :
    public QWidget
{
	Q_OBJECT
 
public:
    bool isPanelShown = false;
    FloatingNotePanel(QWidget* parent);
    void updateUi();
    void switchPanel();

signals:
    void SignalDarkenBackground();
    void SignalBrightenBackground();

public slots:
    void darkenOrBrightenRequest();
    void moveSlider(int buttonIndex);

private:
    QVBoxLayout* m_floatingNotePanelLayout;
    QLabel* m_floatingNotePanelTitle;
    QWidget* m_floatingNotePanelTabBar;
    QHBoxLayout* m_floatingNotePanelTabBarLayout;
    QPushButton* m_allFloatingNoteButton;
    QPushButton* m_successFloatingNoteButton;
    QPushButton* m_informationFloatingNoteButton;
    QPushButton* m_warningFloatingNoteButton;
    QPushButton* m_errorFloatingNoteButton;
    QWidget* m_floatingNotePanelTabBarSlider;
    QWidget* m_floatingNoteButtonSlider;

    QWidget* m_floatingNoteContent;
    QList<QPushButton*> m_floatingNoteButtonList;

    void setupUi();
    void updateProperty(int buttonIndex);
};

