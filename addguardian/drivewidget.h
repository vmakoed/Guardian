#ifndef DRIVEWIDGET_H
#define DRIVEWIDGET_H

#include <QPushButton>
#include <QLabel>

class DriveWidget : public QPushButton
{
    Q_OBJECT

private:
    QLabel *driveLetterLabel;
    QLabel *driveNameLabel;

public:
    QString getDriveLetter();

    explicit DriveWidget(QWidget *parent, QString driveLetter, QString driveName);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void uncheck();
    void check();
};

#endif // DRIVEWIDGET_H
