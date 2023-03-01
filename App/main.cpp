#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QStringLiteral("user interface"));
    w.show();
    w.resize(QSize(800, 480));
    return a.exec();
}
