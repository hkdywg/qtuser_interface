#ifndef CITYMANAGERWIDGET_H
#define CITYMANAGERWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "qtlistwidget.h"
#include "qtwidgetbase.h"

class CityManagerWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit CityManagerWidget(QWidget *parent = 0);
    ~CityManagerWidget();

signals:
    void signalCityChanged(const QString &city);

public slots:

private:
    QLineEdit       *m_lineEdit;
    QtListWidget    *m_listCitys;

    QString          m_strCurrentCity;

private:
    void InitWidget();

private slots:
    void SltSearcCitys();
    void SltCitySelected(QtListWidgetItem *item);
    void SltToolBtnClicked(int index);
protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // CITYMANAGERWIDGET_H
