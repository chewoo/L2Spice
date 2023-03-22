#include "mainwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFile stylesheetfile("./Combinear.qss");
//    stylesheetfile.open(QFile::ReadOnly);
//    QString stylesheet = QLatin1String(stylesheetfile.readAll());
//    a.setStyleSheet(stylesheet);


    MainWindow w;
    w.show();
    return a.exec();
}
