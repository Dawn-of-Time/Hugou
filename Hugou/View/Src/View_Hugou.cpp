#include "View/Include/View_Hugou.h"

HugouView::HugouView()
    : QWidget()
{
    // 注册qml
    qmlRegisterType<HugouView>("HugouModules", 1, 0, "Hugou");
    // 字体载入
    QString fontDir = "Resource/font";
    QDir dir(fontDir);
    QStringList files = dir.entryList(QDir::Files);
    foreach(const QString & fileName, files) {
        QString filePath = dir.absoluteFilePath(fileName);
        QFontDatabase::addApplicationFont(filePath);
    }

    // --无边框窗口
    // 注：使用无边框窗口的一个目标是方便自定义标题栏。事实上，使用Qt::CustomizeWindowHint标志会更方便一些，
    //    因为Qt::FramelessWindowHint标志将会一并移出窗口边缘的拉伸效果，同时并不自带圆角效果。遗憾的是，
    //    使用Qt::CustomizeWindowHint标志后，会在窗口的顶端残留白条，并不美观。因此考虑使用
    //    Qt::FramelessWindowHint标志，其余功能自行实现。
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint |
        Qt::WindowMinimizeButtonHint | Qt::FramelessWindowHint);
    setupUi();
    // 接入windows API。
    HWND hWnd = (HWND)winId();
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    SetWindowLongPtr(
        hWnd,
        GWL_STYLE,
        style
        | WS_MINIMIZEBOX
        | WS_MAXIMIZEBOX
        | WS_CAPTION
        | CS_DBLCLKS
        | WS_THICKFRAME
    );
    // 为FloatingNoteManager指定Hugou
    FloatingNoteManager::getManager()->setHugou(this);
}

void HugouView::scale()
{
    if (this->isMaximized())
        ShowWindow((HWND)winId(), SW_RESTORE);
    else
        ShowWindow((HWND)winId(), SW_MAXIMIZE);
}

void HugouView::setupUi()
{
    // 1 主窗口
    // --基本设置
    this->setObjectName("hugou");
    this->setMinimumSize(minimumMainWindowWidth, minimumMainWindowHeight);
    this->resize(mainWindowWidth, mainWindowHeight);
    this->setWindowIcon(QIcon(":/icon/Hugou.ico"));

    // 2 主布局
    m_generalLayout = new QVBoxLayout(this);
    m_generalLayout->setSpacing(0);
    m_generalLayout->setContentsMargins(0, 0, 0, 0);
    // ------标题栏
    m_titleBarView = new TitleBarView(this);
    // ----侧边栏与堆叠控件
    m_asideBarAndStackedWidget = new QWidget(this);
    m_asideBarAndStackedWidget->setObjectName("asideBarAndStackedWidget");
    m_asideBarAndStackedLayout = new QHBoxLayout(m_asideBarAndStackedWidget);
    m_asideBarAndStackedLayout->setSpacing(0);
    m_asideBarAndStackedLayout->setContentsMargins(0, 0, 0, 0);
    // ----侧边栏
    m_asideBarView = new AsideBarView(m_asideBarAndStackedWidget);
    // ------堆叠控件
    m_stackedWidgetContainer = new QWidget(m_asideBarAndStackedWidget);
    m_stackedWidgetLayout = new QHBoxLayout(m_stackedWidgetContainer);
    m_stackedWidgetLayout->setSpacing(0);
    m_stackedWidgetLayout->setContentsMargins(5, 0, 0, 0);
    m_stackedWidget = new QStackedWidget(m_stackedWidgetContainer);
    m_stackedWidget->setObjectName("stackedWidget");
    m_stackedWidgetOpacityEffect = new QGraphicsOpacityEffect(m_stackedWidget);
    m_stackedWidgetOpacityEffect->setOpacity(1);
    m_stackedWidget->setGraphicsEffect(m_stackedWidgetOpacityEffect);
    m_stackedWidgetOpacityEffect->setEnabled(false);
    m_stackedSwitchFadeOutAnimation = new QPropertyAnimation(m_stackedWidgetOpacityEffect, "opacity", m_stackedWidget);
    m_stackedSwitchFadeOutAnimation->setStartValue(1);
    m_stackedSwitchFadeOutAnimation->setEndValue(0);
    m_stackedSwitchFadeOutAnimation->setDuration(200);
    connect(m_stackedSwitchFadeOutAnimation, &QPropertyAnimation::finished, [&]()
        {
            m_stackedWidget->setCurrentIndex(m_objectiveStackedWidgetIndex);
            m_stackedSwitchFadeInAnimation->start();
        });
    m_stackedSwitchFadeInAnimation = new QPropertyAnimation(m_stackedWidgetOpacityEffect, "opacity", m_stackedWidget);
    m_stackedSwitchFadeInAnimation->setStartValue(0);
    m_stackedSwitchFadeInAnimation->setEndValue(1);
    m_stackedSwitchFadeInAnimation->setDuration(200);
    connect(m_stackedSwitchFadeInAnimation, &QPropertyAnimation::finished, this, &HugouView::disableGraphicsEffect);
    m_scheduleView = new ScheduleView(m_stackedWidget);
    //m_projectView = new ProjectView(m_stackedWidget);
    //m_achievementView = new AchievementView(m_stackedWidget);
    //m_documentView = new DocumentView(m_stackedWidget);
    //m_applicationRepoView = new ApplicationRepoView(m_stackedWidget);
    //m_extentionView = new ExtentionView(m_stackedWidget);
    //m_recycleBinView = new RecycleBinView(m_stackedWidget);
    m_preferenceView = new PreferenceView(m_stackedWidget);
    m_stackedWidget->addWidget(m_scheduleView);
    //m_stackedWidget->addWidget(m_achievementView);
    //m_stackedWidget->addWidget(m_documentView);
    //m_stackedWidget->addWidget(m_applicationRepoView);
    //m_stackedWidget->addWidget(m_extentionView);
    //m_stackedWidget->addWidget(m_recycleBinView);
    m_stackedWidget->addWidget(m_preferenceView);

    m_stackedWidget->setCurrentWidget(m_scheduleView);

    m_stackedWidgetLayout->addWidget(m_stackedWidget);

    m_asideBarAndStackedLayout->addWidget(m_asideBarView);
    m_asideBarAndStackedLayout->addWidget(m_stackedWidgetContainer);

    m_generalLayout->addWidget(m_titleBarView);
    m_generalLayout->addWidget(m_asideBarAndStackedWidget);

    // 全局控件
    m_darkenWidget = new QWidget(this);
    m_darkenWidget->setObjectName("darkenWidget");
    m_darkenWidget->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight);
    m_darkenWidget->setHidden(true);
    //m_floatingNotePanel = new FloatingNotePanel(this);
    m_globalTopView = new GlobalTopView(this);

    retranslateUi();
}

void HugouView::changeStackedWidget(int index)
{
    enableGraphicsEffect();
    m_objectiveStackedWidgetIndex = index;
    m_stackedSwitchFadeOutAnimation->start();
}

void HugouView::retranslateUi()
{

}

void HugouView::disableGraphicsEffect()
{
    m_stackedWidgetOpacityEffect->setEnabled(false);
}

void HugouView::enableGraphicsEffect()
{
    m_stackedWidgetOpacityEffect->setEnabled(true);
}

HugouView::Area HugouView::getArea(const QPoint& mousePos)
{
    m_currentMainWindowGeometry = this->geometry();
    if (mousePos.y() >= 0 && mousePos.y() < edgeWidth)
    {
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return TOPLEFT; }
        else if (mousePos.x() >= edgeWidth && mousePos.x() <= (m_currentMainWindowGeometry.width() - edgeWidth)) { return TOP; }
        else if (mousePos.x() > (m_currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= m_currentMainWindowGeometry.width()) { return TOPRIGHT; }
    }
    else if (mousePos.y() >= edgeWidth && mousePos.y() <= (m_currentMainWindowGeometry.height() - edgeWidth))
    {
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return LEFT; }
        else if (mousePos.x() > (m_currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= m_currentMainWindowGeometry.width()) { return RIGHT; }
    }
    else if (mousePos.y() > (m_currentMainWindowGeometry.height() - edgeWidth) && mousePos.y() < m_currentMainWindowGeometry.height())
    {
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return BOTTOMLEFT; }
        else if (mousePos.x() >= edgeWidth && mousePos.x() <= (m_currentMainWindowGeometry.width() - edgeWidth)) { return BOTTOM; }
        else if (mousePos.x() > (m_currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= m_currentMainWindowGeometry.width()) { return BOTTOMRIGHT; }
    }
    if (m_titleBarView->isOnDragZone(mousePos))
    {
        return DRAGZONE;
    }
    return NOTAREA;
}

QRect HugouView::customScale(const Area& area, const QRect& currentMainWindowGeometry, const QPoint& change)
{
    QRect newMainWindowGeometry = currentMainWindowGeometry;
    bool widthInvalid = (newMainWindowGeometry.width() < mainWindowWidth);
    bool heightInvalid = (newMainWindowGeometry.height() < mainWindowHeight);
    switch (area)
    {
    case TOPLEFT:
    {
        newMainWindowGeometry.setTopLeft(currentMainWindowGeometry.topLeft() + change);
        if (heightInvalid) newMainWindowGeometry.setTop(newMainWindowGeometry.top() - change.y());
        if (widthInvalid) newMainWindowGeometry.setLeft(newMainWindowGeometry.left() - change.x());
        break;
    }
    case TOP:
    {
        newMainWindowGeometry.setTop(currentMainWindowGeometry.top() + change.y());
        if (heightInvalid) newMainWindowGeometry.setTop(newMainWindowGeometry.top() - change.y());
        break;
    }
    case TOPRIGHT:
    {
        newMainWindowGeometry.setTopRight(currentMainWindowGeometry.topRight() + change);
        if (heightInvalid) newMainWindowGeometry.setTop(newMainWindowGeometry.top() - change.y());
        if (widthInvalid) newMainWindowGeometry.setRight(newMainWindowGeometry.right() - change.x());
        break;
    }
    case LEFT:
    {
        newMainWindowGeometry.setLeft(currentMainWindowGeometry.left() + change.x());
        if (widthInvalid) newMainWindowGeometry.setLeft(newMainWindowGeometry.left() - change.x());
        break;
    }
    case RIGHT:
    {
        newMainWindowGeometry.setRight(currentMainWindowGeometry.right() + change.x());
        if (widthInvalid) newMainWindowGeometry.setRight(newMainWindowGeometry.right() - change.x());
        break;
    }
    case BOTTOMLEFT:
    {
        newMainWindowGeometry.setBottomLeft(currentMainWindowGeometry.bottomLeft() + change);
        if (heightInvalid) newMainWindowGeometry.setBottom(newMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) newMainWindowGeometry.setLeft(newMainWindowGeometry.left() - change.x());
        break;
    }
    case BOTTOM:
    {
        newMainWindowGeometry.setBottom(currentMainWindowGeometry.bottom() + change.y());
        if (heightInvalid) newMainWindowGeometry.setBottom(newMainWindowGeometry.bottom() - change.y());
        break;
    }
    case BOTTOMRIGHT:
    {
        newMainWindowGeometry.setBottomRight(currentMainWindowGeometry.bottomRight() + change);
        if (heightInvalid) newMainWindowGeometry.setBottom(newMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) newMainWindowGeometry.setRight(newMainWindowGeometry.right() - change.x());
        break;
    }
    case NOTAREA: { break; }
    default: { break; }
    }
    return newMainWindowGeometry;
}

void HugouView::darken()
{
    QPalette palette;
    palette.setColor(m_darkenWidget->backgroundRole(), QColor(0, 0, 0, 150));
    m_darkenWidget->setPalette(palette);
    m_darkenWidget->setAutoFillBackground(true);
    m_darkenWidget->setHidden(false);
    if (sender()->objectName() == "floatingNotePanel") m_floatingNotePanel->switchPanel();
}

void HugouView::brighten()
{
    m_darkenWidget->setHidden(true);
    if (sender()->objectName() == "floatingNotePanel") m_floatingNotePanel->switchPanel();
}

void HugouView::closeHugou()
{
    ConfigurationHelper::getHelper()->syncConfiguration();
    this->close();
}

// 父类函数重写
bool HugouView::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    MSG* msg = static_cast<MSG*>(message);
    switch (msg->message)
    {
        // 注：拦截WM_NCCALCSIZE消息，以防后续坐标计算错位。
    case WM_NCCALCSIZE:
    {
        *result = HTNOWHERE;
        return true;
    }
    case WM_ACTIVATE:
    {
        MARGINS margins = { 0, 1, 0, 1 };
        HRESULT hr = DwmExtendFrameIntoClientArea(msg->hwnd, &margins);
        *result = hr;
        return true;
    }
    case WM_NCHITTEST:
    {
        *result = HTCLIENT;
        QPoint globalPos = QCursor::pos();
        QPoint windowPos = mapFromGlobal(globalPos);

        Area area = getArea(windowPos);
        switch (area)
        {
        case TOPLEFT: { *result = HTTOPLEFT; break; }
        case TOP: { *result = HTTOP; break; }
        case TOPRIGHT: { *result = HTTOPRIGHT; break; }
        case LEFT: { *result = HTLEFT; break; }
        case RIGHT: { *result = HTRIGHT; break; }
        case BOTTOMLEFT: { *result = HTBOTTOMLEFT; break; }
        case BOTTOM: { *result = HTBOTTOM; break; }
        case BOTTOMRIGHT: { *result = HTBOTTOMRIGHT; break; }
        case DRAGZONE: { *result = HTCAPTION; break; }
        case NOTAREA: { *result = HTCLIENT; break; }
        default: { break; }
        }

        QPushButton* button = m_titleBarView->m_scaleButton;
        QPoint localPos = button->mapFromGlobal(globalPos);
        if (m_titleBarView->isOnMaxButton(windowPos))
        {
            // 这里的触发机制如下：
            // 当控件未接受到Enter事件时，undermouse()返回false。因此，在鼠标首次悬浮于最大化按钮之上时（undermouse()为false），
            // 发送Enter事件，此后当鼠标在最大化按钮区域内移动时，undermouse()为true。
            QMouseEvent mouseEvent = QMouseEvent(button->underMouse() ? QEvent::MouseMove : QEvent::Enter, localPos, globalPos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            button->update();
            *result = HTMAXBUTTON;
            return true;
        }
        else
        {
            if (button->underMouse())
            {
                // 同样的，只有接受到Leave事件后，undermouse()才返回false。
                QMouseEvent mouseEvent = QMouseEvent(QEvent::Leave, localPos, globalPos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
                QCoreApplication::sendEvent(button, &mouseEvent);
                button->update();
                return true;
            }
        }
        if (*result != HTCLIENT) return true;
        return false;
    }
    case WM_NCLBUTTONDOWN:
    {
        if (msg->wParam == HTMAXBUTTON) {
            QPushButton* button = m_titleBarView->m_scaleButton;
            QMouseEvent mouseEvent = QMouseEvent(QEvent::MouseButtonPress, QPoint(), QPoint(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            *result = HTNOWHERE;
            return true;
        }
        break;
    }
    case WM_NCLBUTTONUP:
    {
        if (msg->wParam == HTMAXBUTTON) {
            QPushButton* button = m_titleBarView->m_scaleButton;
            QMouseEvent mouseEvent = QMouseEvent(QEvent::MouseButtonRelease, QPoint(), QPoint(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            return true;
        }
        break;
    }
    case WM_NCMOUSEHOVER:
    case WM_NCMOUSELEAVE:
    case WM_NCMOUSEMOVE:
    {
        if (msg->wParam == HTMAXBUTTON)
        {
            *result = HTNOWHERE;
            return true;
        }
    }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void HugouView::changeEvent(QEvent* event) {
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange) {
        switch (windowState()) {
        case Qt::WindowMaximized: {
            m_titleBarView->m_scaleButton->setIcon(QIcon(":/icon/restore_black.ico"));
            int border = GetSystemMetrics(SM_CXSIZEFRAME);
            setContentsMargins(border, border, border, border);
            break;
        }
        case Qt::WindowNoState:
            m_titleBarView->m_scaleButton->setIcon(QIcon(":/icon/maximum_black.ico"));
            setContentsMargins(0, 0, 0, 0);
            break;
        default:
            break;
        }
    }
}


void HugouView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    FloatingNoteManager* floatingNoteManager = FloatingNoteManager::getManager();
    // 浮动消息
    if (floatingNoteManager->m_isAnimating || (floatingNoteManager->getShownFloatingNote()))
    {
        //qDebug() << "***Start adjusting***";
        floatingNoteManager->adjustFloatingNote();
    }

    // 设置页表单
    m_preferenceView->adjustSizeHint();

    //m_floatingNotePanel->updateUi();
    m_darkenWidget->resize(this->width(), this->height() - titleFrameHeight);
    m_globalTopView->setGeometry(m_asideBarAndStackedWidget->geometry());

    if (m_stackedSwitchFadeInAnimation->state() == QPropertyAnimation::Running ||
        m_stackedSwitchFadeOutAnimation->state() == QPropertyAnimation::Running)
    {
        m_stackedSwitchFadeInAnimation->stop();
        m_stackedSwitchFadeOutAnimation->stop();
        m_stackedWidgetOpacityEffect->setOpacity(1);
        disableGraphicsEffect();
        m_stackedWidget->setCurrentIndex(m_objectiveStackedWidgetIndex);
    }
}