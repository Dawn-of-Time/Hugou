#pragma once
#include "MenuItem.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QPainter>
#include <QSlider>
#include <QPainterPath>
#include <QRegularExpressionValidator>
#include <QScrollArea>
#include "Utils/Include/Utils_DragFilter.h"

class ColorArea :
    public QWidget
{
    Q_OBJECT

public:
    ColorArea(QWidget* parent) { updateBackground(); };
    void setHue(const qreal& hue) { m_hue = hue; updateBackground();  update(); };
    int getHue() { return m_hue; }

signals:
    void SignalClicked(const QPoint& position);

private:
    int m_hue = 0;
    QPixmap m_background;
    QPushButton* m_colorAreaButton;

    void updateBackground()
    {
        // 使用QLinearGradient来绘制比逐像素绘制高效的多。
        m_background = QPixmap(size());
        m_background.fill(Qt::transparent);
        QPainter pixmapPainter(&m_background);
        QLinearGradient horizontalGradient(0, 0, width(), 0);
        for (int saturation = 0; saturation <= 255; ++saturation) {
            qreal pos = saturation / 255.0;
            horizontalGradient.setColorAt(pos, QColor::fromHsv(m_hue, saturation, 255));
        }
        pixmapPainter.fillRect(rect(), horizontalGradient);
        QLinearGradient verticalGradient(0, 0, 0, height());
        verticalGradient.setColorAt(0, Qt::white);
        verticalGradient.setColorAt(1, Qt::black);
        pixmapPainter.setCompositionMode(QPainter::CompositionMode_Multiply);
        pixmapPainter.fillRect(rect(), verticalGradient);
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton)
            emit SignalClicked(event->pos());
    }

    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(rect(), m_background);
    }
};

class HueSlider :
    public QSlider
{
public:
    HueSlider(QWidget* parent) : QSlider(Qt::Horizontal, parent)
    {
        setRange(0, 359);
        setValue(0);
    }
private:
    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QRect backgroundRect = rect();
        QPainterPath path;
        path.addRoundedRect(backgroundRect, 10, 10);
        painter.setClipPath(path);
        QLinearGradient gradient(backgroundRect.topLeft(), backgroundRect.topRight());
        for (int hue = 0; hue <= 359; hue += 1) {
            qreal pos = hue / 359.0;
            gradient.setColorAt(pos, QColor::fromHsv(hue, 255, 255));
        }
        painter.fillRect(backgroundRect, gradient);
        painter.setClipping(false);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(backgroundRect, 10, 10);
        QSlider::paintEvent(event);
    }
};

class ColorPaletteMenuItem :
    public MenuItem
{
    Q_OBJECT

public:
    ColorPaletteMenuItem(const QString& title, QWidget* menu);
    void setColor(const QString& colorHex);
    void recall() override;
    QString save() override;

private:
    // hex的控制是精准的，hsv的控制是粗略的，尽可能使用hex来控制。
    // 以下初始化是为了使滑块出现在二维面的中心和滑动条的最左端。
    QColor m_oldColor = QColor::fromHsv(0, 128, 128);
    QColor m_newColor = QColor::fromHsv(0, 128, 128);
    QWidget* m_widget;
    QVBoxLayout* m_widgetLayout;
    QWidget* m_colorAreaWidget;
    QVBoxLayout* m_colorAreaWidgetLayout;
    ColorArea* m_colorArea;
    QPushButton* m_colorAreaButton;
    DragFilter* m_filter;
    HueSlider* m_colorSlider;
    QWidget* m_hexSelection;
    QHBoxLayout* m_hexSelectionLayout;
    QLabel* m_hexLabel;
    QLabel* m_wellNumberLabel;
    QWidget* m_hexColor;
    QLineEdit* m_hexLineEdit;
    QWidget* m_colorRepo;
    QGridLayout* m_colorRepoLayout;

    void setupUi();
    void updateFromButton(const QPoint& position);
    void updateFromHex(const QString& hex);
    QStringList m_colorExamples = {
        "#F8CCD9", "#F8CCD9", "#F4B3C5", "#EF8BA6", "#E25778", 
        "#EFE5ED", "#E9D5E3", "#D4B4CD", "#AA7BA0", "#894E7B",
        "#FBDAC6", "#F8C4B2", "#F4AA8D", "#F19071", "#E27260",
        "#EFE8E8", "#D7CCC9", "#BBAAA5", "#A1877E", "#8E6D63",
        "#E2EEF7", "#D1E7F5", "#96C2E2", "#6FA3D0", "#3A868D",
        "#D5EBE3", "#C4E4DA", "#A3D6CA", "#6EC3B3", "#008D75",
        "#F5DF7A", "#F2BE38", "#D29C2F", "#A97C26", "#885C20",
        "#F7B3AC", "#F9877D", "#F54D40", "#D0241C", "#941B14",
    };
};

