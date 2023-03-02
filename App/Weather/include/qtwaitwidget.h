#ifndef QTWAITWIDGET_H
#define QTWAITWIDGET_H

#include "qtwidgetbase.h"
#include <QTimer>

class QtWaitWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit QtWaitWidget(QWidget *parent = 0);
    ~QtWaitWidget();

    void SetPixmap(const QPixmap &pixmap);

    void Start(int interval);
    void SetText(const QString &text);
signals:

private:
    qreal   m_rotate;
    qreal   m_step;

    QString m_strText;

    QTimer *m_timer;
    QPixmap m_pixmap;
    int     m_nInterval;

private slots:
    void SltBeginToRefresh();

protected:

    void paintEvent(QPaintEvent *);
};

#endif // QTWAITWIDGET_H
