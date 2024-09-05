#include "View_Hugou.h"

HugouView::HugouView()
    : QWidget()
{
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
}

void HugouView::setupUi()
{
    // 1 主窗口
    // --基本设置
    this->setObjectName("hugou");
    this->setMinimumSize(mainWindowWidth, mainWindowHeight);
    this->resize(960, 640);

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
    m_stackedWidgetLayout->setContentsMargins(5, 0, 5, 5);
    m_stackedWidget = new QStackedWidget(m_stackedWidgetContainer);
    m_stackedWidget->setObjectName("stackedWidget");
    // --------堆叠控件：WorkSpace
    m_workSpaceWidget = new WorkSpace(m_stackedWidget);
    // --------堆叠控件：Settings
    m_settingsView = new SettingsView(m_stackedWidget);

    m_stackedWidget->addWidget(m_workSpaceWidget);
    m_stackedWidget->addWidget(m_settingsView);
    m_stackedWidget->setCurrentWidget(m_workSpaceWidget);

    m_stackedWidgetLayout->addWidget(m_stackedWidget);

    m_asideBarAndStackedLayout->addWidget(m_asideBarView);
    m_asideBarAndStackedLayout->addWidget(m_stackedWidgetContainer);

    m_generalLayout->addWidget(m_titleBarView);
    m_generalLayout->addWidget(m_asideBarAndStackedWidget);

    // 全局控件
    m_blurWidget = new QWidget(this);
    m_blurWidget->setObjectName("blurWidget");
    m_blurWidget->setGeometry(0, titleFrameHeight, mainWindowWidth, mainWindowHeight);
    m_blurWidget->setHidden(true);
    m_blurEffect = new QGraphicsBlurEffect(this);
    m_blurEffect->setBlurRadius(30);
    m_blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
    m_blurWidget->setGraphicsEffect(m_blurEffect);
    m_floatingNotePanel = new FloatingNotePanel(this);
    m_globalTopView = new GlobalTopView(this);

    retranslateUi();
} 

void HugouView::startToApplyThemeResource(QString theme)
{
    m_globalTopView->setSource("qrc:/qml/themeApplyMedia.qml");
    m_globalTopView->setHint("Upcoming theme: " + theme);
    m_globalTopView->fadeIn();
}

bool HugouView::applyThemeResourceForStartup(QString generalStyleSheet, QString asideBarStyleSheet, QString settingsStyleSheet)
{
    bool applyFlag = true;
    if (generalStyleSheet.isEmpty() || asideBarStyleSheet.isEmpty() || settingsStyleSheet.isEmpty())
    {
        applyFlag = false;
        emit SettingsHelper::getHelper()->triggerError(10100);
        generalStyleSheet = defaultGeneralStyleSheet;
        asideBarStyleSheet = defaultAsideBarStyleSheet;
        settingsStyleSheet = defaultSettingsStyleSheet;
    }
    this->setStyleSheet(generalStyleSheet);
    m_asideBarView->setStyleSheet(asideBarStyleSheet);
    m_settingsView->setStyleSheet(settingsStyleSheet);
    return applyFlag;
}

bool HugouView::applyThemeResource(QString generalStyleSheet, QString asideBarStyleSheet, QString settingsStyleSheet)
{
    bool applyFlag = true;
    if (!generalStyleSheet.isEmpty() && !asideBarStyleSheet.isEmpty() && !settingsStyleSheet.isEmpty())
    {
        this->setStyleSheet(generalStyleSheet);
        m_asideBarView->setStyleSheet(asideBarStyleSheet);
        m_settingsView->setStyleSheet(settingsStyleSheet);
    }
    else
    {
        applyFlag = false;
        emit SettingsHelper::getHelper()->triggerError(10100);
    }
    return applyFlag;
}

void HugouView::endToApplyThemeResourceFinished()
{
    m_globalTopView->fadeOut();
}

void HugouView::changeStackedWidget(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}

void HugouView::retranslateUi()
{
    this->setWindowTitle(QCoreApplication::translate("HugouClass", "Hugou", nullptr));
}

HugouView::Area HugouView::getArea(QPoint mousePos)
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

QRect HugouView::customScale(Area area, QRect currentMainWindowGeometry, QPoint change)
{
    QRect tempMainWindowGeometry = currentMainWindowGeometry;
    QRect newMainWindowGeometry = currentMainWindowGeometry;
    bool widthInvalid = (tempMainWindowGeometry.width() < mainWindowWidth);
    bool heightInvalid = (tempMainWindowGeometry.height() < mainWindowHeight);
    switch (area)
    {
    case TOPLEFT:
    {
        tempMainWindowGeometry.setTopLeft(currentMainWindowGeometry.topLeft() + change);
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case TOP:
    {
        tempMainWindowGeometry.setTop(currentMainWindowGeometry.top() + change.y());
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        break;
    }
    case TOPRIGHT:
    {
        tempMainWindowGeometry.setTopRight(currentMainWindowGeometry.topRight() + change);
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case LEFT:
    {
        tempMainWindowGeometry.setLeft(currentMainWindowGeometry.left() + change.x());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case RIGHT:
    {
        tempMainWindowGeometry.setRight(currentMainWindowGeometry.right() + change.x());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case BOTTOMLEFT:
    {
        tempMainWindowGeometry.setBottomLeft(currentMainWindowGeometry.bottomLeft() + change);
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case BOTTOM:
    {
        tempMainWindowGeometry.setBottom(currentMainWindowGeometry.bottom() + change.y());
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        break;
    }
    case BOTTOMRIGHT:
    {
        tempMainWindowGeometry.setBottomRight(currentMainWindowGeometry.bottomRight() + change);
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case NOTAREA: { break; }
    default: { break; }
    }
    newMainWindowGeometry = tempMainWindowGeometry;
    return newMainWindowGeometry;
}

void HugouView::blur()
{
    m_screenShot = QPixmap(m_asideBarAndStackedWidget->size());
    m_asideBarAndStackedWidget->render(&m_screenShot);
    QPalette palette;
    palette.setBrush(m_blurWidget->backgroundRole(), QBrush(m_screenShot));
    m_blurWidget->setPalette(palette);
    m_blurWidget->setAutoFillBackground(true);
    m_blurWidget->setHidden(false);
    if (sender()->objectName() == "floatingNotePanel") m_floatingNotePanel->switchPanel();
}

void HugouView::clearBlur()
{
    m_blurWidget->setHidden(true);
    m_floatingNotePanel->switchPanel();
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
        // 为了获取到正确的全局鼠标位置，应将GET_X_LPARAM和GET_Y_LPARAM得到的结果除以缩放倍数。
        double scale = getScale();
        QPoint globalPos = QPoint(GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)) / scale;
        QPoint windowPos = globalPos - this->pos();

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

        QPushButton* button = m_titleBarView->m_scaledButton;
        QPoint localPos = button->mapFromGlobal(globalPos);
        if (m_titleBarView->isOnMaxButton(windowPos))
        {
            // 这里的触发机制如下：
            // 当控件未接受到Enter事件时，undermouse()返回false。因此，在鼠标首次悬浮于最大化按钮之上时（undermouse()为false），
            // 发送Enter事件，此后当鼠标在最大化按钮区域内移动时，undermouse()为true。
            setCursor(QCursor(Qt::PointingHandCursor));
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
                setCursor(QCursor(Qt::ArrowCursor));
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
            QPushButton* button = m_titleBarView->m_scaledButton;
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
            QPushButton* button = m_titleBarView->m_scaledButton;
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
    if (event->type() == QEvent::WindowStateChange) {
        switch (windowState()) {
        case Qt::WindowMaximized: {
            m_titleBarView->m_scaledButton->setIcon(QIcon(":/icon/restore_w.png"));
            int border = GetSystemMetrics(SM_CXSIZEFRAME);
            setContentsMargins(border, border, border, border);
            break;
        }
        case Qt::WindowNoState:
            m_titleBarView->m_scaledButton->setIcon(QIcon(":/icon/maximum_w.png"));
            setContentsMargins(0, 0, 0, 0);
            break;
        default:
            break;
        }
    }
    QWidget::changeEvent(event);
}

void HugouView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    // 浮动消息
    if (floatingNoteManager.isAnimating || (floatingNoteManager.getShownFloatingNote()))
    {
        //qDebug() << "***Start adjusting***";
        floatingNoteManager.adjustFloatingNote(this);
    }

    // 设置页表单
    m_settingsView->adjustSizeHint();

    m_floatingNotePanel->updateUi();
    m_blurWidget->resize(this->width(), this->height() - titleFrameHeight);
    m_globalTopView->updateUi(this);

    if (!m_blurWidget->isHidden())
    {
        m_screenShot = QPixmap(m_asideBarAndStackedWidget->size());
        m_asideBarAndStackedWidget->render(&m_screenShot);
        QPalette palette;
        palette.setBrush(m_blurWidget->backgroundRole(), QBrush(m_screenShot));
        m_blurWidget->setPalette(palette);
        m_blurWidget->setAutoFillBackground(true);
    }
}