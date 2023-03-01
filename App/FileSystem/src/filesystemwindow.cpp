/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : filesystemwindow.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#include "filesystemwindow.h"

#include <QBoxLayout>
#include <QSplitter>
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>

FileSystemWindow::FileSystemWindow(QWidget *parent) : QtAnimationWidget(parent)
{
#ifdef __arm__
    m_strRootPath = QString("/");
#else
    m_strRootPath = QString(qApp->applicationDirPath());
#endif
    InitWidget();

    QTimer::singleShot(500, this, SLOT(InitModel()));
}

FileSystemWindow::~FileSystemWindow()
{

}

void FileSystemWindow::InitWidget()
{
    m_addressBar = new QtAddressBar(this);
    connect(m_addressBar, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));
    connect(m_addressBar, SIGNAL(signalAddress(QString)), this, SLOT(SltAddressChanged(QString)));
    m_addressBar->setAddress(m_strRootPath);

    QHBoxLayout *horLayout = new QHBoxLayout();
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setSpacing(0);

    QWidget *widgetHome = new QWidget(this);
    widgetHome->setStyleSheet(QString("background-color: #474540"));
    widgetHome->setFixedWidth(33);
    horLayout->addWidget(widgetHome);

    QWidget *widgetRecent = new QWidget(this);
    widgetRecent->setObjectName("widgetRecent");
    widgetRecent->setStyleSheet(QString("QWidget#widgetRecent{background-color: #605d53;}"
                                        "QPushButton{border:none; border-bottom: 1px solid #aaaaaa;"
                                        "background-color: none; font-family:'%1';"
                                        "font: 18px; color: #ffffff; min-height: 35px; text-align: left; padding-left: 10px}"
                                        "QPushButton:pressed{background-color: #f17a49;}").arg("思源黑体 CN Normal"));
    horLayout->addWidget(widgetRecent, 1);


    QVBoxLayout *verLayoutRecent = new QVBoxLayout(widgetRecent);
    verLayoutRecent->setContentsMargins(0, 0, 0, 0);
    verLayoutRecent->setSpacing(0);
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QPushButton *btnHome = new QPushButton(widgetRecent);
    btnGroup->addButton(btnHome, 0);
    btnHome->setText("home");
    verLayoutRecent->addWidget(btnHome);

    QPushButton *btnRoot = new QPushButton(widgetRecent);
    btnRoot->setText("root");
    btnGroup->addButton(btnHome, 1);
    verLayoutRecent->addWidget(btnRoot);

    verLayoutRecent->addStretch();
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(SltBtnRecentClicked(int)));

    // file list
    m_listView = new QtPressMoveListView(this);
    m_listView->SetIconMode();
    m_listView->setDragDropMode(QListView::NoDragDrop);
    horLayout->addWidget(m_listView, 6);

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addWidget(m_addressBar, 1);
    verLayoutAll->addLayout(horLayout, 7);
}

void FileSystemWindow::InitModel()
{
    m_model = new QFileSystemModel(this);
    m_model->setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    m_model->setRootPath(m_strRootPath);

    m_listView->setModel(m_model);
    m_listView->setRootIndex(m_model->index(m_strRootPath));
#ifdef __arm__
    connect(m_listView, SIGNAL(clicked(QModelIndex)), this, SLOT(SltItemClicked(QModelIndex)));
#else
    connect(m_listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(SltItemClicked(QModelIndex)));
#endif
}

void FileSystemWindow::SltItemClicked(const QModelIndex &index)
{
    if (m_model->isDir(index)) {
        m_strRootPath = m_model->filePath(index);
        m_addressBar->setAddress(m_strRootPath);
        m_listView->setRootIndex(m_model->index(m_strRootPath));
    }
    else {

    }
}

void FileSystemWindow::SltAddressChanged(const QString &addr)
{
    m_listView->setRootIndex(m_model->index(addr));
}

void FileSystemWindow::SltNotePadHide()
{
}

void FileSystemWindow::SltBtnRecentClicked(int index)
{
    if (0 == index) {
        m_listView->setRootIndex(m_model->index("/home/"));
    } else {
        m_listView->setRootIndex(m_model->index("/root/"));
    }
}

void FileSystemWindow::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_listView->setIconSize(QSize(60 * m_scaleX, 60 * m_scaleY));
    m_listView->setGridSize(QSize(100 * m_scaleX, 100 * m_scaleY));
    QWidget::resizeEvent(e);
}

