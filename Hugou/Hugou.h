#pragma once

#include <QMainWindow>
#include <QPainter>
#include "ui_Hugou.h"
#include "PDFEdit.h"
#include "Setting.h"

class Hugou : public QMainWindow
{

    Q_OBJECT

public:
    Hugou(Setting* setting, QWidget* parent = nullptr);
    ~Hugou();
    Setting* receiveSetting;
    PDFEdit* pdfEdit;
    Ui_HugouClass ui;
    // Ä£ºýÐ§¹û
    QGraphicsBlurEffect* blurEffect;
    QTimer blurTimer;
    void switchOverSearchButton(bool msg);
    void search();
    void raiseReadingSettingError();
    void raiseSavingSettingError();

protected slots:
    void changeStackedWidget(int index);
    void checkIsLineEditNull();
    void deleteSearchText();
    void openPDFEditFunction();
    void blurStackedWidget();
    void clearStackedWidget();

private:
    int blurRadius = 0;
    void paintEvent(QPaintEvent* event) override
    {
        QBitmap bmp(this->size());
        bmp.clear();
        QPainter painter(&bmp);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(Qt::black));
        painter.drawRoundedRect(this->rect(), 12, 12, Qt::AbsoluteSize);
        this->setMask(bmp);
    }
};
