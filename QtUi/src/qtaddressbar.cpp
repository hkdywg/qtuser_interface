#include "qtaddressbar.h"

#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>

#define FONT_FAMILY "思源黑体 CN Normal"

AddressLineEdit::AddressLineEdit(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = 620;
    m_nBaseHeight = 40;

    m_font.setFamily(FONT_FAMILY);
    m_font.setPixelSize(18);
    m_nMargin = 10;
    m_nSplitWidth = 4;

    m_nIndex = -1;
}

AddressLineEdit::~AddressLineEdit()
{

}

void AddressLineEdit::setAddress(const QString &addr)
{
    m_strAddrPath = addr;
    QStringList strAddress = m_strAddrPath.split("/");
    ClearItem();
    QFont font(FONT_FAMILY);
    font.setPixelSize(18);
    QFontMetrics fm(font);

    QRect rect(0, 0, m_nMargin, m_nBaseHeight);

    for (int i = 0; i < strAddress.size(); i++) {
        QString strAddr = strAddress.at(i);
#if (QT_VERSION > QT_VERSION_CHECK(5, 11, 0))
        int nWidth = fm.horizontalAdvance(strAddr, strAddr.length());
#else
        int nWidth = fm.width(strAddr, strAddr.length());
#endif
        rect = QRect(rect.right()+ 2, rect.top(), nWidth + m_nSplitWidth + 1, rect.height());
        m_addressItems.insert(i, new AddressItem(i, strAddr, rect));
      }

    m_nIndex = m_addressItems.size() - 1;
    this->update();
}

QString AddressLineEdit::getAddress()
{
    QString strPath = "";
    for (int i = 0; i < m_addressItems.size(); i++) {
        if (i > m_nIndex) break;
        strPath += m_addressItems.value(i)->address();
        strPath.append("/");
    }
qDebug() << "get address is " << strPath;
    return strPath;
}

void AddressLineEdit::appendDir(const QString &dir)
{
    Q_UNUSED(dir);
}

void AddressLineEdit::SltBackAddress()
{
    if (m_nIndex > 0) {
        CurrentPathChanged(m_nIndex - 1);
    }
}

void AddressLineEdit::SltNextAddress()
{
    if (m_nIndex < (m_addressItems.size() - 1)) {
        CurrentPathChanged(m_nIndex + 1);
    }
}

void AddressLineEdit::ClearItem(int startId)
{
    foreach (AddressItem *item, m_addressItems) {
        if (item->id() >= startId) {
            m_addressItems.remove(item->id());
            delete item;
            item = NULL;
        }
    }
}

void AddressLineEdit::CurrentPathChanged(int index)
{
    if (index == m_nIndex) return;
    m_nIndex = index;
    QString strPath = getAddress();
    this->update();
    emit signalAddress(strPath);
}

void AddressLineEdit::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#fafafa"));
    painter.drawRoundedRect(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), 8, 8);

    QFont font(FONT_FAMILY);
    font.setPixelSize(18);
    painter.setFont(m_font);

    painter.setBrush(Qt::NoBrush);

    foreach (AddressItem *item, m_addressItems) {
        painter.setPen(m_nIndex == item->id() ? QColor("#00ff00") : QColor("#3c3c3c"));

        painter.drawText(item->rect(), Qt::AlignCenter, item->address());
        if (item->id() < (m_addressItems.size() - 1)) {
            painter.drawText(QRect(item->rect().right(), item->rect().top(), m_nSplitWidth+2, m_nBaseHeight),
                             Qt::AlignCenter, "/");
        }
    }
}

void AddressLineEdit::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    foreach (AddressItem *item, m_addressItems) {
        ScaleRect(rect, item->rect());
        if (rect.contains(e->pos())) {
            CurrentPathChanged(item->id());
            this->update();
            break;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////
QtAddressBar::QtAddressBar(QWidget *parent) : QtWidgetTitleBar(parent)
{
    this->SetBackground(QColor("#474540"));
    m_nBaseWidth = 800;
    m_nBaseHeight = 60;

    InitWidget();
}

QtAddressBar::~QtAddressBar()
{

}

void QtAddressBar::setAddress(const QString &addr)
{
    m_addrLineEdit->setAddress(addr);
}

QString QtAddressBar::getAddress()
{
    return m_addrLineEdit->getAddress();
}

void QtAddressBar::SltBtnClicked(int index)
{
    if (0 == index) {
        emit signalBackHome();
    } else if (1 == index) {
        m_addrLineEdit->SltBackAddress();
    } else if (2 == index) {
        m_addrLineEdit->SltNextAddress();
    }
}

void QtAddressBar::InitWidget()
{
    m_addrLineEdit = new AddressLineEdit(this);
    connect(m_addrLineEdit, SIGNAL(signalAddress(QString)), this, SIGNAL(signalAddress(QString)));
}

void QtAddressBar::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_addrLineEdit->setFixedSize(620 * m_scaleX, 40 * m_scaleY);
    m_addrLineEdit->move(110 * m_scaleX, 10 * m_scaleY);
    QWidget::resizeEvent(e);
}

