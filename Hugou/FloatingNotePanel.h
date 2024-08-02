#pragma once
#include <QLabel>
#include "ui_FloatingNotePanel.h"
#include "Const.h"

class FloatingNotePanel :
    public QLabel
{
	Q_OBJECT
 
public:
    bool isPanelShown = false;
    FloatingNotePanel(QWidget* parent);
    void updateUi(QWidget* Hugou);

signals:
    void blurBackground();
    void clearBackground();

public slots:
    void showPanel();

private:
    Ui_FloatingNotePanel ui;
};

