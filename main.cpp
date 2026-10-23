#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile styleFile("style.qss");
    if (!styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Stylesheet konnte nicht geöffnet werden!";
    }
    else
    {
        a.setStyleSheet(QLatin1String(styleFile.readAll()));
    }
    w.show();
    return QApplication::exec();
}
