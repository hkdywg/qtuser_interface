#include "mainwindow.h"
#include <QBoxLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    InitWidget();
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitWidget()
{
    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);

    m_launcherWidget = new LauncherWidget(this);
    m_launcherWidget->SetWallpaper(QPixmap(":/images/mainwindow/background.png"));
    connect(m_launcherWidget, SIGNAL(currentItemClicked(int)), this, SLOT(SltCurrentAppChanged(int)));
    verLayout->addWidget(m_launcherWidget, 1);

    qDebug() << "Init Widget Done" << endl;

#if 0
    if (NULL == m_musicWidget) {
        m_musicWidget = new MusicPlayer(this);
        connect(m_musicWidget, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
        connect(m_musicWidget, SIGNAL(signalAnimationFinished()), this, SLOT(SltAppStartOk()));
    }
#endif
}
