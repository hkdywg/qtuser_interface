#ifndef QTPIXMAPBUTTON_H
#define QTPIXMAPBUTTON_H

#include <QObject>
#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPixmapButton {
#else
class QtPixmapButton  {
#endif
public:
    QtPixmapButton();
    QtPixmapButton(int id, QRect rect, QString text, QColor normal, QColor pressed);
    QtPixmapButton(QPixmap pixmapNormal, QPixmap pixmapPressed);
    QtPixmapButton(int id, QRect rect, QPixmap pixmapNormal, QPixmap pixmapPressed);

    int id();

    QString text();
    void setText(const QString &text);

    QRect rect();
    void setRect(QRect rect);

    QColor color();
    void setColor(QColor normal, QColor pressed);

    QPixmap pixmap();
    void setPixmap(const QPixmap &normal, const QPixmap &pressed);

    void setPressed(bool bOk);
    bool isPressed();

    void setVisible(bool bOk);
    bool isVisible();

    void setCheckAble(bool bOk);
    bool isCheckAble();

    void setChecked(bool bOk);
    bool isChecked();

    void setEnable(bool bOk);
    bool isEnabled();

    QSize size() const;
private:
    int m_nId;
    QRect m_rect;
    QString m_strText;

    QColor m_colorNormal;
    QColor m_colorPressed;

    QPixmap m_pixmapNormal;
    QPixmap m_pixmapPressed;

    bool  m_bPressed;
    bool  m_bVisible;

    bool  m_bCheckAble;
    bool  m_bChecked;

    bool  m_bEnable;
};

#endif // QTPIXMAPBUTTON_H
