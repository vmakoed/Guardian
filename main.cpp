#include "mainwindow.h"
#include <QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // If you include a *qss file from qrc (project resources), you'll have to recompile the whole project every time
    // you run it. So for now we're leaving it this way (insert your projects' folder path before /Guardian/res).

    QFile File("C:/Users/Victor Makoed/Google Drive/Qt Creator/Guardian/res/stylesheet.qss");

    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    a.setStyleSheet(StyleSheet);

    MainWindow w;
    w.show();

    return a.exec();
}
