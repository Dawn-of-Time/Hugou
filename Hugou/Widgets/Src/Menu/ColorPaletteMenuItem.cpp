#include "Widgets/Include/Menu/ColorPaletteMenuItem.h"

ColorPaletteMenuItem::ColorPaletteMenuItem(const QString& title, QWidget* menu)
	:MenuItem(title, menu)
{
	setupUi();
    setCentralWidget(m_widget);
    connect(m_colorArea, &ColorArea::SignalClicked, [&](const QPoint& position) { m_colorAreaButton->move(position);  updateFromButton(position);});
    connect(m_colorSlider, &HueSlider::valueChanged, m_colorArea, [&](int value) { m_colorArea->setHue(value); updateFromButton(m_colorAreaButton->pos());});
    connect(m_filter, &DragFilter::SignalPositionChanged, this, &ColorPaletteMenuItem::updateFromButton);
    connect(m_hexLineEdit, &QLineEdit::editingFinished, [&]() {if (m_hexLineEdit->text().size() == 6)  updateFromHex("#" + m_hexLineEdit->text());});
}

void ColorPaletteMenuItem::setColor(const QString& colorHex) 
{ 
    m_oldColor = QColor(colorHex);
    updateFromHex(colorHex);
    m_hexLineEdit->setText(colorHex.right(6));
}

void ColorPaletteMenuItem::recall()
{
    updateFromHex(m_oldColor.name());
    m_hexLineEdit->setText(m_oldColor.name().right(6));
}

QString ColorPaletteMenuItem::save()
{
    return m_newColor.name();
}

void ColorPaletteMenuItem::setupUi()
{
    // ×ÖÌåÇåµ¥
    QFont hexLabelFont =  QFont("NeverMind", 12, QFont::Normal);
    QFont hexFont = QFont("NeverMind", 10, QFont::Normal);

    m_widget = new QWidget(this);
    m_widgetLayout = new QVBoxLayout(m_widget);
    m_widgetLayout->setContentsMargins(0, 0, 0, 0);
    m_widgetLayout->setSpacing(5);

    m_colorAreaWidget = new QWidget(m_widget);
    m_colorAreaWidget->setFixedSize(250, 250);
    m_colorAreaWidgetLayout = new QVBoxLayout(m_colorAreaWidget);
    m_colorAreaWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_colorAreaWidgetLayout->setSpacing(0);
    m_colorAreaWidgetLayout->setAlignment(Qt::AlignCenter);

    m_colorArea = new ColorArea(m_colorAreaWidget);
    m_colorArea->setFixedSize(230, 230);
    m_colorAreaWidgetLayout->addWidget(m_colorArea);

    m_colorAreaButton = new QPushButton(m_colorAreaWidget);
    m_colorAreaButton->setFixedSize(20, 20);
    m_colorAreaButton->setStyleSheet(
        "QPushButton {"
        "background: transparent;"
        "border: 5px solid white;"
        "border-radius: 10px;"
        "}"
    );
    m_colorAreaButton->setMouseTracking(true);
    m_filter = new DragFilter(this);
    m_colorAreaButton->installEventFilter(m_filter);
    m_colorAreaButton->raise();

    m_colorSlider = new HueSlider(m_widget);
    m_colorSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "background: transparent;"
        "}"
        "QSlider::handle:horizontal {"
        "background: transparent;"
        "width: 10px;"
        "border: 5px solid white;"
        "border-radius: 10px;"
        "}"
    );
    m_hexSelection = new QWidget(m_widget);
    m_hexSelectionLayout = new QHBoxLayout(m_hexSelection);
    m_hexSelectionLayout->setContentsMargins(5, 0, 5, 0);
    m_hexSelectionLayout->setSpacing(5);
    m_hexLabel = new QLabel("Hex", m_hexSelection);
    m_hexLabel->setFixedHeight(20);
    m_hexLabel->setFont(hexLabelFont);
    m_hexColor = new QWidget(m_hexSelection);
    m_hexColor->setFixedSize(20, 20);
    m_wellNumberLabel = new QLabel("#", m_hexSelection);
    m_wellNumberLabel->setFixedHeight(20);
    m_wellNumberLabel->setFont(hexLabelFont);
    m_hexLineEdit = new QLineEdit(m_oldColor.name().right(6), m_hexSelection);
    m_hexLineEdit->setFixedSize(80, 20);
    m_hexLineEdit->setFont(hexFont);
    QRegularExpression regExp("[a-zA-Z0-9]{0,6}");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regExp, m_hexLineEdit);
    m_hexLineEdit->setValidator(validator);
    m_hexSelectionLayout->addWidget(m_hexLabel);
    m_hexSelectionLayout->addStretch();
    m_hexSelectionLayout->addWidget(m_hexColor);
    m_hexSelectionLayout->addWidget(m_wellNumberLabel);
    m_hexSelectionLayout->addWidget(m_hexLineEdit);

    QScrollArea* area = new QScrollArea(m_widget);
    area->setFixedHeight(100);
    area->setWidgetResizable(true);
    area->setStyleSheet("background-color: transparent");
    m_colorRepo = new QWidget(area);
    m_colorRepoLayout = new QGridLayout(m_colorRepo);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
        {
            QPushButton* button = new QPushButton(m_colorRepo);
            button->setFixedSize(20, 20);
            button->setStyleSheet(QString("border-radius: 5px; background-color: %1").arg(m_colorExamples[i * 5 + j]));
            m_colorRepoLayout->addWidget(button, i, j);
        }
    area->setWidget(m_colorRepo);

    m_widgetLayout->addWidget(m_colorAreaWidget);
    m_widgetLayout->addWidget(m_colorSlider);
    m_widgetLayout->addWidget(m_hexSelection);
    m_widgetLayout->addWidget(area);
}

void ColorPaletteMenuItem::updateFromButton(const QPoint& position)
{
    m_newColor = QColor::fromHsv(m_colorArea->getHue(), position.x() * 255 / 230, 255 - position.y() * 255 / 230);
    m_hexColor->setStyleSheet(QString("border-radius: 5px; background-color: %1").arg(m_newColor.name()));
    m_hexColor->update();
    m_hexLineEdit->setText(m_newColor.name().right(6));
}

void ColorPaletteMenuItem::updateFromHex(const QString& hex)
{
    QColor color = QColor(hex);
    if (color.hue() == -1) color.setHsv(m_newColor.hue(), color.saturation(), color.value());
    m_newColor = color;
    m_hexColor->setStyleSheet(QString("border-radius: 5px; background-color: %1").arg(m_newColor.name()));
    m_hexColor->update();
    m_colorAreaButton->move(230 * m_newColor.saturation() / 255, 230 * (255 - m_newColor.value()) / 255);
    m_colorSlider->blockSignals(true);
    m_colorSlider->setValue(m_newColor.hue());
    m_colorArea->setHue(m_newColor.hue());
    m_colorSlider->blockSignals(false);
}