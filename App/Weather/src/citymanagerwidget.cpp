#include "citymanagerwidget.h"
#include "citybook.h"

#include <QPainter>
#include <QPushButton>
#include <QDebug>
#include <QBoxLayout>

CityManagerWidget::CityManagerWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/weather/city_bg.png"));
    m_strCurrentCity = "test";

    InitWidget();
}

CityManagerWidget::~CityManagerWidget()
{
    delete m_listCitys;
    m_listCitys = NULL;
}

void CityManagerWidget::InitWidget()
{
    m_btns.insert(0, new QtPixmapButton(0, QRect(10, 20, 40, 40), QPixmap(":/images/weather/ic_back.png"), QPixmap(":/images/weather/ic_back_pre.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(723, 95, 67, 35), tr("搜索"), QColor("#169bd5"), QColor("#11bbdd")));

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(tr(""));
    m_lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    connect(m_lineEdit, SIGNAL(returnPressed()), this, SLOT(SltSearcCitys()));
    m_lineEdit->setStyleSheet(QString("QLineEdit{border-radius:none; border-radius: 10px;"
                                      "background-color: #ffffff; font-family: '%1'; "
                                      "color: #333333; font: 16px;}").arg("思源黑体 CN Normal"));

    m_listCitys = new QtListWidget(this);
    m_listCitys->SetBackground(QColor("#fafafa"));
    m_listCitys->setVisible(false);
    m_listCitys->setFont(QFont("思源黑体 CN Normal"));
    m_listCitys->setHoriazontal(false);
    m_listCitys->setAlignment(Qt::AlignVCenter);
    m_listCitys->setItemSize(45);
    m_listCitys->setScaleSize(800, 155);

    connect(m_listCitys, SIGNAL(currentItemClicked(QtListWidgetItem*)), this, SLOT(SltCitySelected(QtListWidgetItem*)));
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltToolBtnClicked(int)));

}

void CityManagerWidget::SltSearcCitys()
{
    if (m_strCurrentCity == m_lineEdit->text()) return;

    m_strCurrentCity = m_lineEdit->text();
    QStringList strCitys = CityBook::Instance()->searchCitys(m_strCurrentCity);
    QMap<int, QtListWidgetItem*> mapCitys;
    for (int i = 0; i < strCitys.size(); i++) {
        mapCitys.insert(i, new QtListWidgetItem(i, strCitys.at(i)));
    }
    m_listCitys->SetItems(mapCitys);
}

void CityManagerWidget::SltCitySelected(QtListWidgetItem *item)
{
    emit signalCityChanged(item->m_strText);
}

void CityManagerWidget::SltToolBtnClicked(int index)
{
    m_lineEdit->clearFocus();

    if (0 == index) {
        emit signalBackHome();
    } if (1 == index) {
#ifdef Q_OS_WIN32
        m_lineEdit->clearFocus();
#endif
        SltSearcCitys();
    }
}

void CityManagerWidget::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_lineEdit->resize(700 * m_scaleX, 35 * m_scaleY);
    m_lineEdit->move(10, 95 * m_scaleY);

    m_listCitys->resize(this->width(), 155 * m_scaleY);
    m_listCitys->move(0, 140 * m_scaleY);

    QWidget::resizeEvent(e);
}

void CityManagerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    painter.drawPixmap(0, 0, m_pixmapBackground);

    QFont font("思源黑体 CN Bold");
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    QRect rect(1, 0, m_nBaseWidth - 2, 80);
    painter.drawText(rect, Qt::AlignCenter, tr("城市选择"));

    QtPixmapButton *btnBack = m_btns.value(0);
    painter.drawPixmap(btnBack->rect(), btnBack->pixmap());

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#ffffff"));
    rect = QRect(rect.left(), rect.bottom() + 10, rect.width(), 45);
    painter.drawRoundedRect(rect, 5, 5);

    QtPixmapButton *btnSearch = m_btns.value(1);
    painter.setBrush(btnSearch->color());
    painter.drawRoundedRect(btnSearch->rect(), 5, 5);

    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    painter.drawText(btnSearch->rect(), Qt::AlignCenter, btnSearch->text());
}

