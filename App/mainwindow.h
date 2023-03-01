#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "launcherwidget.h"
#include "qtwidgetbase.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LauncherWidget      *m_launcherWidget;
    QMap<int, LauncherItem*> m_launchItems;


private:
    void InitWidget();

};
#endif // MAINWINDOW_H
