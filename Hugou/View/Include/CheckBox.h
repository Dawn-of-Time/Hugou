#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsEffect>

class CheckBox : public QPushButton {
    Q_OBJECT

public:
    enum Status {
        Checked, Unchecked
    };
    CheckBox(QWidget* parent, Status status = Status::Unchecked);

signals:
    void SignalBorderProgressChanged();

private:
    Status m_status;
    QPropertyAnimation* m_animation;
    QVBoxLayout* m_layout;
    QLabel* m_icon;
    QGraphicsOpacityEffect* m_effect;
    void changeStatus();
    void enableGraphicsEffect();
    void disableGraphicsEffect();
};