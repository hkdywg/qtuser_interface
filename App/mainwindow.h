#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "launcherwidget.h"
#include "qtwidgetbase.h"
#include "filesystemwindow.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LauncherWidget      *m_launcherWidget;
    QMap<int, LauncherItem*> m_launchItems;

    QtAnimationWidget   *m_widgetWorkSpace;
    int                  m_nCurrentIndex;
    bool                 m_bStartApp;


private:
    void InitWidget();
    void InitDesktop();

private slots:
    void SltCurrentAppChanged(int index);
    void SltBackHome();
    void SltAppStartOk();

};
#endif // MAINWINDOW_H
