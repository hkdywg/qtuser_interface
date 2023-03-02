#ifndef FILESYSTEMWINDOW_H
#define FILESYSTEMWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableView>
#include "qtaddressbar.h"
#include "qtwidgetbase.h"
#include "qtlistwidget.h"
#include "qtpressmovelistview.h"

#include <QFileSystemModel>

class FileSystemWindow : public QtAnimationWidget
{
    Q_OBJECT
public:
    FileSystemWindow(QWidget *parent = 0);
    ~FileSystemWindow();

private:
    QtAddressBar        *m_addressBar;
    QtPressMoveListView *m_listView;
    QFileSystemModel    *m_model;

    QString              m_strRootPath;

private:
    void InitWidget();
    Q_SLOT void InitModel();

private slots:
    void SltItemClicked(const QModelIndex &index);
    void SltAddressChanged(const QString &addr);
    void SltNotePadHide();
    void SltBtnRecentClicked(int index);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // FILESYSTEMWINDOW_H
