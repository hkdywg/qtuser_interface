#ifndef QTPRESSMOVELISTVIEW_H
#define QTPRESSMOVELISTVIEW_H

#include <QWidget>
#include <QListView>
#include <QScrollBar>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPressMoveListView : public QListView {
#else
class QtPressMoveListView : public QListView {
#endif
    Q_OBJECT
public:
    explicit QtPressMoveListView(QWidget *parent = 0);
    ~QtPressMoveListView();

    void SetIconMode();

private:
    bool m_bPressed;
    QPoint m_startPos;
    QScrollBar *m_scrollbar;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // QTPRESSMOVELISTVIEW_H
