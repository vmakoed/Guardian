#include "maincontroller.h"
#include <QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile File("C:/Users/Victor Makoed/Google Drive/Qt Creator/Guardian/res/stylesheet.qss");

    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    a.setStyleSheet(StyleSheet);

    MainController *mainController = new MainController;
    mainController->launch();

    return a.exec();
}
