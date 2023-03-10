#include "qtwaitwidget.h"
#include <QPainter>

QtWaitWidget::QtWaitWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_rotate = 0;
    m_step = 0;

    m_nBaseWidth = 800;
    m_nBaseHeight = 42;

    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltBeginToRefresh()));
}

QtWaitWidget::~QtWaitWidget()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    delete m_timer;
    m_timer = NULL;
}

void QtWaitWidget::SetPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    this->update();
}

void QtWaitWidget::Start(int interval)
{
    m_nInterval = interval;
    m_timer->start();
}

void QtWaitWidget::SetText(const QString &text)
{
    m_strText = text;
}

void QtWaitWidget::SltBeginToRefresh()
{
    m_rotate += 9;
    if (m_rotate >= 360) {
        m_rotate = 0;
    }

    m_step += 50;
    if (m_step >= m_nInterval) {
        m_rotate = 0;
        m_step = 0;
        m_timer->stop();
    }

    this->update();
}

void QtWaitWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    QFont font("思源黑体 CN Normal");
    font.setPixelSize(18);
    painter.setFont(font);
    int nTW = getTextWidthByFont(painter.font(), m_strText);
    painter.setPen(QColor("#ffffff"));;

    if (m_pixmap.isNull()) {
        painter.fillRect(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), QColor("#fafafa"));
        painter.drawText(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), Qt::AlignCenter, m_strText);
    } else {
        painter.save();
        int nX = (m_nBaseWidth - m_pixmap.width() - nTW - 10) / 2;
        int nY = (m_nBaseHeight - m_pixmap.height()) / 2;
        painter.translate(nX + m_pixmap.width() / 2, nY + m_pixmap.height() / 2);
        painter.rotate(m_rotate);
        painter.translate(-(nX + m_pixmap.width() / 2), -(nY + m_pixmap.height() / 2));
        painter.drawPixmap(nX, nY, m_pixmap);
        painter.restore();
        painter.drawText(QRect(nX + m_pixmap.width() + 10, 0, nTW, m_nBaseHeight), Qt::AlignCenter, m_strText);
    }
}
