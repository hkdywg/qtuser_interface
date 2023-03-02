#include "mainwindow.h"
#include <QBoxLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_widgetWorkSpace = NULL;
    m_nCurrentIndex = -1;
    m_bStartApp = false;

    InitWidget();
    InitDesktop();
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
}

void MainWindow::InitDesktop()
{
#if 1
    int nPage = 0;
    m_launchItems.insert(0, new LauncherItem(0, nPage, tr("文件管理"), QPixmap(":/images/mainwindow/ic_file.png")));
    m_launchItems.insert(3, new LauncherItem(3, nPage, tr("相册"), QPixmap(":/images/mainwindow/ic_photos.png")));
    m_launchItems.insert(5, new LauncherItem(5, nPage, tr("天气"), QPixmap(":/images/mainwindow/ic_weather.png")));
    m_launchItems.insert(7, new LauncherItem(7, nPage, tr("时钟"), QPixmap(":/images/mainwindow/ic_clock.png")));
    m_launchItems.insert(10, new LauncherItem(10, nPage, tr("计算器"), QPixmap(":/images/mainwindow/ic_calc.png")));


    m_launchItems.insert(1, new LauncherItem(1, nPage, tr("视频播放"), QPixmap(":/images/mainwindow/ic_video.png")));
    m_launchItems.insert(4, new LauncherItem(4, nPage, tr("相机"), QPixmap(":/images/mainwindow/ic_camera.png")));
    m_launchItems.insert(11, new LauncherItem(11, nPage, tr("音乐播放"), QPixmap(":/images/mainwindow/ic_music.png")));

#ifdef BUILD_WITH_WEBVIEW
    m_launchItems.insert(14, new LauncherItem(14, nPage, tr("网络浏览器"), QPixmap(":/images/mainwindow/ic_webview.png")));
#endif
    m_launchItems.insert(15, new LauncherItem(15, nPage, tr("汽车仪表"), QPixmap(":/images/mainwindow/ic_car.png")));
    m_launchItems.insert(16, new LauncherItem(16, nPage, tr("背光调节"), QPixmap(":/images/mainwindow/ic_backlight.png")));
    m_launchItems.insert(23, new LauncherItem(23, nPage, tr("系统设置"), QPixmap(":/images/mainwindow/ic_setting.png")));

    m_launchItems.insert(18, new LauncherItem(18, nPage, tr("录音"), QPixmap(":/images/mainwindow/ic_record.png")));

    m_launcherWidget->SetItems(m_launchItems);
#endif
}

void MainWindow::SltCurrentAppChanged(int index)
{
    qDebug() << "app item is be toched, index is " << index << endl;

    if (m_bStartApp) return;
    m_launcherWidget->setEnabled(false);
    m_bStartApp = true;

    if (NULL != m_widgetWorkSpace ) {
        if (m_nCurrentIndex != index) {
            disconnect(m_widgetWorkSpace, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
            delete m_widgetWorkSpace;
            m_widgetWorkSpace = NULL;
        } else {
            m_widgetWorkSpace->setVisible(true);
            m_widgetWorkSpace->StartAnimation(QPoint(this->width(), this->height()), QPoint(0, 0), 300, true);
            return;
        }
    }
    switch (index) {
    case 0: {
        m_widgetWorkSpace = new FileSystemWindow(this);
        qDebug() << "file system item is created!" << endl;
    }
        break;

    default:
        m_bStartApp = false;
        m_launcherWidget->setEnabled(true);
        m_nCurrentIndex = -1;
        break;
    }

    if (NULL != m_widgetWorkSpace) {
        m_widgetWorkSpace->resize(this->size());
        connect(m_widgetWorkSpace, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
        connect(m_widgetWorkSpace, SIGNAL(signalAnimationFinished()), this, SLOT(SltAppStartOk()));

        m_nCurrentIndex = index;
        m_widgetWorkSpace->setVisible(true);
        m_widgetWorkSpace->StartAnimation(QPoint(this->width(), this->height()), QPoint(0, 0), 300, true);
    }
}

void MainWindow::SltBackHome()
{
    if (NULL != m_widgetWorkSpace) {
        m_widgetWorkSpace->StartAnimation(QPoint(0, 0), QPoint(-this->width(), -this->height()), 300, false);
    }
}

void MainWindow::SltAppStartOk()
{
    m_bStartApp = false;
    m_launcherWidget->setEnabled(true);
}


